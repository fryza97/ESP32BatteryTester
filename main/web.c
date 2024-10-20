const char *web_string1 = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border-radius: 12px;\
  background-color: light-gray;\
  border-style: groove;\
  border-color: red;\
  color: red;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {} /* RED */\
</style>\
</head>\
<body>\
\
<h1>Battery tester on ESP32</h1>\
<p>Click button to make measurment.<br>\
Make sure voltage source is connected propertly<br>\ 
Red probe MAX 12 V<br>\
Green probe MAX 3.3 V<br>\
Black probe to negative pole\
</p>\
\
<button class=\"button button1\" onclick=\"window.location.href='/'\">Get Voltage</button>\
\
<p>Voltage - CH1: ";

const char *web_string2 = "<br></p>\
<p>Voltage - CH2:";

const char *web_string3 = "</p>\
\
</body>\
</html>";