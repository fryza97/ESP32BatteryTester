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
<h1>Voltage meter on ESP32</h1>\
<p>Click button to make measurment. Make sure is voltage<br> source is connected propertly to voltage connector.</p>\
\
<button class=\"button button1\" onclick=\"window.location.href='/'\">Get Voltage</button>\
\
<p>Voltage:";

const char *web_string2 = "</p>\
\
</body>\
</html>";