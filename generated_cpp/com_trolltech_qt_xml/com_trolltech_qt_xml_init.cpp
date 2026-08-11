#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

// Register base classes before derived DOM wrappers so their ScriptValue
// prototypes can inherit the complete Qt 6 hierarchy.
QScriptValue qtscript_create_QDomNodeList_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomImplementation_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomNode_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomNamedNodeMap_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomDocument_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomEntity_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomCharacterData_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomAttr_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomElement_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomDocumentFragment_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomEntityReference_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomProcessingInstruction_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomNotation_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomDocumentType_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomComment_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomText_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomCDATASection_class(QScriptEngine *engine);
void qtscript_initialize_QtXml_namespace(QScriptValue &extensionObject);

static const char * const qtscript_com_trolltech_qt_xml_class_names[] = {
    "QDomNodeList",
    "QDomImplementation",
    "QDomNode",
    "QDomNamedNodeMap",
    "QDomDocument",
    "QDomEntity",
    "QDomCharacterData",
    "QDomAttr",
    "QDomElement",
    "QDomDocumentFragment",
    "QDomEntityReference",
    "QDomProcessingInstruction",
    "QDomNotation",
    "QDomDocumentType",
    "QDomComment",
    "QDomText",
    "QDomCDATASection"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_xml_class_functions[] = {
    qtscript_create_QDomNodeList_class,
    qtscript_create_QDomImplementation_class,
    qtscript_create_QDomNode_class,
    qtscript_create_QDomNamedNodeMap_class,
    qtscript_create_QDomDocument_class,
    qtscript_create_QDomEntity_class,
    qtscript_create_QDomCharacterData_class,
    qtscript_create_QDomAttr_class,
    qtscript_create_QDomElement_class,
    qtscript_create_QDomDocumentFragment_class,
    qtscript_create_QDomEntityReference_class,
    qtscript_create_QDomProcessingInstruction_class,
    qtscript_create_QDomNotation_class,
    qtscript_create_QDomDocumentType_class,
    qtscript_create_QDomComment_class,
    qtscript_create_QDomText_class,
    qtscript_create_QDomCDATASection_class
};

void qtscript_initialize_com_trolltech_qt_xml_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < int(sizeof(qtscript_com_trolltech_qt_xml_class_names)
                            / sizeof(qtscript_com_trolltech_qt_xml_class_names[0])); ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_xml_class_names[i],
            qtscript_com_trolltech_qt_xml_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
    qtscript_initialize_QtXml_namespace(extensionObject);
}
