TEMPLATE = subdirs
SUBDIRS = qtscript_core \
          qtscript_gui \
          qtscript_network \
          qtscript_sql \
          qtscript_xml \
          qtscript_widgets \
          qtscript_printsupport \
          qtscript_uitools \
          qtscript_svg \
          qs_eval

qtscript_gui.depends = qtscript_core
qtscript_network.depends = qtscript_core
qtscript_sql.depends = qtscript_core
qtscript_xml.depends = qtscript_core
qtscript_widgets.depends = qtscript_core
qtscript_printsupport.depends = qtscript_core qtscript_gui qtscript_widgets
qtscript_uitools.depends = qtscript_core qtscript_widgets
qtscript_svg.depends = qtscript_core qtscript_gui qtscript_widgets
qs_eval.depends = qtscript_core qtscript_gui qtscript_network qtscript_sql qtscript_xml qtscript_widgets qtscript_printsupport qtscript_uitools qtscript_svg
