function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

var ipv4 = new QHostAddress("127.0.0.1");
var ipv6 = new QHostAddress("::1");
check(ipv4.isLoopback()
      && ipv4.protocol().valueOf() === QAbstractSocket.IPv4Protocol.valueOf(),
      "IPv4 loopback classification failed");
check(ipv6.isLoopback()
      && ipv6.protocol().valueOf() === QAbstractSocket.IPv6Protocol.valueOf(),
      "IPv6 loopback classification failed");
check(ipv4.isInSubnet(new QHostAddress("127.0.0.0"), 8),
      "IPv4 subnet matching failed");
check(!ipv4.isInSubnet(new QHostAddress("10.0.0.0"), 8),
      "IPv4 subnet matching accepted an unrelated network");

// Request attributes and priority are QVariant-backed and are easy to break
// when enum values are regenerated for Qt 6.
var request = new QNetworkRequest(new QUrl("https://example.invalid/api"));
request.setPriority(QNetworkRequest.HighPriority);
check(request.priority().valueOf() === QNetworkRequest.HighPriority.valueOf(),
      "QNetworkRequest priority enum did not round-trip");
request.setHeader(QNetworkRequest.ContentTypeHeader, "application/json");
check(request.header(QNetworkRequest.ContentTypeHeader) === "application/json",
      "QNetworkRequest known-header conversion failed");
request.setRawHeader(new QByteArray("X-Regression"), new QByteArray("one"));
var rawHeaders = request.rawHeaderList();
var foundRegressionHeader = false;
for (var i = 0; i < rawHeaders.length; ++i) {
    if (rawHeaders[i].toString().toLowerCase() === "x-regression")
        foundRegressionHeader = true;
}
check(foundRegressionHeader, "QNetworkRequest raw-header list conversion failed");

// Cookie parsing and raw serialization cover QByteArray/list conversions and
// the secure/HTTP-only flags without relying on an external HTTP service.
var parsed = QNetworkCookie.parseCookies(
    new QByteArray("sid=abc; Path=/; Secure; HttpOnly"));
check(parsed.length === 1, "QNetworkCookie.parseCookies returned the wrong count");
var cookie = parsed[0];
check(cookie.name().toString() === "sid" && cookie.value().toString() === "abc",
      "parsed cookie name/value was corrupted");
cookie.setDomain("example.invalid");
check(cookie.isSecure() && cookie.isHttpOnly() && cookie.path() === "/"
      && cookie.toRawForm().toString().indexOf("sid=abc") === 0,
      "cookie attributes were not preserved in raw serialization");

// Mutable references must exchange both script-owned values and reject
// invalid arguments before changing the receiver.
function checkNetworkSwap(a, b, fingerprint, wrong) {
    var oldA = fingerprint(a), oldB = fingerprint(b), alias = b;
    check(oldA !== oldB, "swap fixtures must differ");
    a.swap(b);
    check(fingerprint(a) === oldB && fingerprint(b) === oldA
          && fingerprint(alias) === oldA, "network swap did not exchange both objects");
    a.swap(b);
    a.swap(a);
    check(fingerprint(a) === oldA && fingerprint(b) === oldB, "network repeat/self swap failed");
    var invalid = [null, undefined, {}, wrong];
    for (var i = 0; i < invalid.length; ++i) {
        var error = null;
        try { a.swap(invalid[i]); } catch (caught) { error = caught; }
        check(error !== null && error.name === "TypeError" && fingerprint(a) === oldA,
              "invalid network swap must throw without changing the receiver");
    }
}
checkNetworkSwap(new QNetworkRequest(new QUrl("https://alpha.example.test/a")),
                 new QNetworkRequest(new QUrl("https://beta.example.test/b")),
                 function(request) { return request.url().toString(); }, new QNetworkProxy());
checkNetworkSwap(new QNetworkProxy(QNetworkProxy.HttpProxy, "alpha.example.test", 8080, "alice", "a"),
                 new QNetworkProxy(QNetworkProxy.Socks5Proxy, "beta.example.test", 1080, "bob", "b"),
                 function(proxy) {
                     return [proxy.type().valueOf(), proxy.hostName(), proxy.port(),
                             proxy.user(), proxy.password()].join("|");
                 }, new QNetworkRequest());

print("Network regression smoke passed");
