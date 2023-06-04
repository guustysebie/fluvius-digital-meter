fuzzers =[
    "/XXX5ID\r\n\r\n!CCCC\r\n",
    "/XXX5ID\r\n\r\n!CCCC\r\n/XXX5ID\r\n\r\n!CCCC\r\n"
]

fuzme1 =  "/XXX5ID\r\n\r\n" \
         "0-0:96.1.1(xxxxxxxxxxxxxxxxxxxxxxxxxxxx)\r\n"\
         "0-1:24.2.3(210204163500W)(00343.925*m3)\r\n"\
         "1-0:21.7.0(00.233kW)\r\n"\
         "!CCCC\r\n";

fuzme2 =  "/XXX5ID\r\n\r\n" \
          "0-0:96.1.1(xxxxxxxxxxxxxxxxxxxxxxxxxxxx)\r\n" \
          "0-1:24.2.3(210204163500W)(00343.925*m3)\r\n" \
          "1-0:21.7.0((00.233kW)\r\n" \
          "!CCCC\r\n";


fuzme3 =  "/XXX5ID\r\n\r\n" \
          "0-0:96.1.1(xxxxxxxxxxxxxxxxxxxxxxxxxxxx)\r\n" \
          "0-1:24.2.3(210204163500W)(00343.925+m3)\r\n" \
          "1-0:21.7.0(00.233kW)\r\n" \
          "!CCCC\r\n";

fuzzers.append(fuzme1)
fuzzers.append(fuzme2)
fuzzers.append(fuzme3)

