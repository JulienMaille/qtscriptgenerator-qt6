function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QHostAddress === "function", "QHostAddress binding was not imported");
check(typeof QNetworkRequest === "function", "QNetworkRequest binding was not imported");
check(typeof QNetworkCookie === "function", "QNetworkCookie binding was not imported");
check(typeof QTcpServer === "function", "QTcpServer binding was not imported");
check(typeof QTcpSocket === "function", "QTcpSocket binding was not imported");

var loopback = new QHostAddress(QHostAddress.LocalHost);
check(loopback.toString() === "127.0.0.1", "IPv4 loopback conversion failed");
check(loopback.protocol() === QAbstractSocket.IPv4Protocol,
      "IPv4 protocol detection failed");

var request = new QNetworkRequest(new QUrl("https://example.invalid/resource"));
request.setRawHeader(new QByteArray("X-Qt6-Smoke"), new QByteArray("network"));
check(request.hasRawHeader(new QByteArray("X-Qt6-Smoke")), "raw request header is missing");
check(request.rawHeader(new QByteArray("X-Qt6-Smoke")).toString() === "network",
      "raw request header conversion failed");
request.setAttribute(QNetworkRequest.Http2AllowedAttribute, true);
request.setAttribute(QNetworkRequest.AutoDeleteReplyOnFinishAttribute, false);
check(request.attribute(QNetworkRequest.Http2AllowedAttribute) === true,
      "Qt 6 HTTP/2 request attribute failed");
check(request.attribute(QNetworkRequest.AutoDeleteReplyOnFinishAttribute) === false,
      "Qt 6 auto-delete request attribute failed");

check(QSsl.TlsV1_3 !== undefined && QSsl.TlsV1_3OrLater !== undefined,
      "Qt 6 TLS 1.3 protocols were not exported");
check(QSsl.Ec !== undefined && QSsl.Dh !== undefined,
      "Qt 6 SSL key algorithms were not exported");
check(QSslSocket.supportsSsl(), "Qt reports no usable SSL backend");
check(QSslSocket.supportedCiphers().length > 0,
      "Qt reports no supported SSL ciphers");

var cookie = new QNetworkCookie(new QByteArray("session"), new QByteArray("qt6"));
cookie.setDomain("example.invalid");
cookie.setPath("/");
cookie.setSecure(true);
check(cookie.name().toString() === "session" && cookie.value().toString() === "qt6",
      "network cookie name/value conversion failed");
check(cookie.domain() === "example.invalid" && cookie.path() === "/" && cookie.isSecure(),
      "network cookie properties failed");

var server = new QTcpServer();
check(server.listen(loopback, 0), "local TCP server failed to listen: " +
      server.errorString());
check(server.serverPort() > 0, "local TCP server did not allocate a port");

var socket = new QTcpSocket();
socket.connectToHost(loopback, server.serverPort());
check(socket.waitForConnected(3000), "local TCP client failed to connect: " +
      socket.errorString());
check(server.waitForNewConnection(3000), "local TCP server did not receive the connection");
check(server.hasPendingConnections(), "local TCP connection was not queued");

var peer = server.nextPendingConnection();
check(peer !== null, "local TCP server returned no peer socket");
check(socket.write(new QByteArray("ping")) === 4, "local TCP write failed");
check(socket.waitForBytesWritten(3000), "local TCP write did not complete");
check(peer.waitForReadyRead(3000), "local TCP peer received no data");
check(peer.readAll().toString() === "ping", "local TCP payload was corrupted");

peer.close();
socket.close();
server.close();
