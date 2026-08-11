function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

var validSvg = '<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20">' +
               '<rect id="one" width="20" height="20" fill="blue"/></svg>';
var renderer = new QSvgRenderer(new QByteArray("<svg"));
check(!renderer.isValid(), "malformed SVG was reported as valid");
check(renderer.load(new QByteArray(validSvg)), "renderer could not recover after malformed input");
check(renderer.isValid() && renderer.elementExists("one"),
      "renderer state was not reset by a successful reload");

var flags = new QtSvg.Options(QtSvg.Tiny12FeaturesOnly, QtSvg.DisableAnimations);
renderer.setOptions(flags);
check((renderer.options.valueOf() & flags.valueOf()) === flags.valueOf(),
      "QtSvg option flags did not survive a renderer round-trip");
renderer.setAnimationEnabled(false);
check(!renderer.isAnimationEnabled(), "animationEnabled setter failed");
renderer.setFramesPerSecond(12);
check(renderer.framesPerSecond === 12, "framesPerSecond setter failed");
QSvgRenderer.setDefaultOptions(QtSvg.NoOption);

var output = new QBuffer();
check(output.open(new QIODevice.OpenMode(QIODevice.ReadWrite)),
      "regression output buffer could not be opened");
var generator = new QSvgGenerator(QSvgGenerator.Svg11);
generator.setOutputDevice(output);
generator.setResolution(144);
check(generator.resolution() === 144, "QSvgGenerator resolution did not round-trip");
check(generator.svgVersion().valueOf() === QSvgGenerator.Svg11.valueOf(),
      "QSvgGenerator SvgVersion enum did not round-trip");
generator.setSize(new QSize(20, 20));
var painter = new QPainter();
check(painter.begin(generator), "generator could not be painted after configuration");
painter.drawLine(0, 0, 19, 19);
check(painter.end(), "generator painter could not be ended");
check(output.size() > 0, "configured generator emitted no output");
output.close();

var widget = new QSvgWidget();
widget.setOptions(new QtSvg.Options(QtSvg.DisableCSSAnimations));
check((widget.options().valueOf() & QtSvg.DisableCSSAnimations.valueOf()) !== 0,
      "widget animation option did not survive a round-trip");
var item = new QGraphicsSvgItem();
item.setSharedRenderer(renderer);
item.setElementId("does-not-exist");
check(item.elementId() === "does-not-exist", "QGraphicsSvgItem elementId did not round-trip");
check(item.boundingRect().width() >= 0 && item.boundingRect().height() >= 0,
      "QGraphicsSvgItem returned invalid bounds for a missing element");
delete item;
widget.close();

print("SVG regression smoke test passed");
