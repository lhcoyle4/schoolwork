<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
</parts>
<sheets>
<sheet>
<plain>
<text x="27.94" y="71.12" size="1.778" layer="91">CLOCK_50</text>
<text x="106.68" y="71.12" size="1.778" layer="91">CLOCK_50</text>
<text x="73.66" y="66.04" size="1.778" layer="91">[7:0] RxData</text>
<text x="73.66" y="60.96" size="1.778" layer="91">RxDone</text>
<text x="27.94" y="66.04" size="1.778" layer="91">PS2_CLK</text>
<text x="27.94" y="60.96" size="1.778" layer="91">PS2_DAT</text>
<text x="154.94" y="71.12" size="1.778" layer="91">LCD_EN</text>
<text x="154.94" y="63.5" size="1.778" layer="91">LCD_RS</text>
<text x="147.32" y="53.34" size="1.778" layer="91">[7:0] LCD_DATA</text>
<text x="154.94" y="43.18" size="1.778" layer="91">LCD_RW</text>
</plain>
<instances>
</instances>
<busses>
<bus name="B$1">
<segment>
<wire x1="88.9" y1="66.04" x2="134.62" y2="66.04" width="0.762" layer="92"/>
<wire x1="134.62" y1="66.04" x2="134.62" y2="53.34" width="0.762" layer="92"/>
<wire x1="134.62" y1="53.34" x2="147.32" y2="53.34" width="0.762" layer="92"/>
</segment>
</bus>
<bus name="B$2">
<segment>
<wire x1="167.64" y1="53.34" x2="185.42" y2="53.34" width="0.762" layer="92"/>
</segment>
</bus>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<wire x1="25.4" y1="76.2" x2="25.4" y2="73.66" width="0.1524" layer="91"/>
<wire x1="25.4" y1="73.66" x2="25.4" y2="66.04" width="0.1524" layer="91"/>
<wire x1="25.4" y1="66.04" x2="25.4" y2="60.96" width="0.1524" layer="91"/>
<wire x1="25.4" y1="60.96" x2="25.4" y2="38.1" width="0.1524" layer="91"/>
<wire x1="25.4" y1="38.1" x2="88.9" y2="38.1" width="0.1524" layer="91"/>
<wire x1="88.9" y1="38.1" x2="88.9" y2="60.96" width="0.1524" layer="91"/>
<wire x1="88.9" y1="60.96" x2="88.9" y2="76.2" width="0.1524" layer="91"/>
<wire x1="88.9" y1="76.2" x2="25.4" y2="76.2" width="0.1524" layer="91"/>
<wire x1="25.4" y1="73.66" x2="17.78" y2="73.66" width="0.1524" layer="91"/>
<junction x="25.4" y="73.66"/>
<wire x1="5.08" y1="73.66" x2="17.78" y2="73.66" width="0.1524" layer="91"/>
<wire x1="17.78" y1="73.66" x2="17.78" y2="81.28" width="0.1524" layer="91"/>
<junction x="17.78" y="73.66"/>
<wire x1="17.78" y1="81.28" x2="109.22" y2="81.28" width="0.1524" layer="91"/>
<wire x1="109.22" y1="81.28" x2="109.22" y2="73.66" width="0.1524" layer="91"/>
<wire x1="25.4" y1="66.04" x2="5.08" y2="66.04" width="0.1524" layer="91"/>
<junction x="25.4" y="66.04"/>
<wire x1="25.4" y1="60.96" x2="5.08" y2="60.96" width="0.1524" layer="91"/>
<junction x="25.4" y="60.96"/>
<wire x1="88.9" y1="60.96" x2="127" y2="60.96" width="0.1524" layer="91"/>
<junction x="88.9" y="60.96"/>
<wire x1="127" y1="60.96" x2="127" y2="71.12" width="0.1524" layer="91"/>
<wire x1="127" y1="71.12" x2="152.4" y2="71.12" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="104.14" y1="38.1" x2="104.14" y2="76.2" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="167.64" y1="76.2" x2="104.14" y2="76.2" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="167.64" y1="38.1" x2="104.14" y2="38.1" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="167.64" y1="38.1" x2="167.64" y2="45.72" width="0.1524" layer="91"/>
<wire x1="167.64" y1="45.72" x2="167.64" y2="63.5" width="0.1524" layer="91"/>
<wire x1="167.64" y1="63.5" x2="167.64" y2="71.12" width="0.1524" layer="91"/>
<wire x1="167.64" y1="71.12" x2="167.64" y2="76.2" width="0.1524" layer="91"/>
<wire x1="167.64" y1="71.12" x2="185.42" y2="71.12" width="0.1524" layer="91"/>
<junction x="167.64" y="71.12"/>
<wire x1="167.64" y1="63.5" x2="185.42" y2="63.5" width="0.1524" layer="91"/>
<junction x="167.64" y="63.5"/>
<wire x1="167.64" y1="45.72" x2="185.42" y2="45.72" width="0.1524" layer="91"/>
<junction x="167.64" y="45.72"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
