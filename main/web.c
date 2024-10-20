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
</style>\
</head>\
<body>\
\
<h1>Battery tester on ESP32</h1>\
\
<p>Click button to take measurement.</p>\
<p>Red probe - MAX 12 V</p>\
<p>Green probe - MAX 3.3 V</p>\
<p>Black probe - connect to negative pole</p>\
\
<button class=\"button\" onclick=\"window.location.href='/'\">Get Voltage</button>\
\
<p>Voltage - CH1: ";

const char *web_string2 = "</p>\
\
<p>Voltage - CH2: ";

const char *web_string3 = "</p>\
</body>\
</html>";

