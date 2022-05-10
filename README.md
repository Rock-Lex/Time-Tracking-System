# Zeiterfassung System

Employee time tracking system.  <br/>

The system scans the bar code or RFID key and then, with the help of Odoo API, logs in or logs out the employee to whom the key is assigned. <br/>

The display shows the number of hours worked, date and time. <br/>

The request is made with the help of libCurl and then parsed with the help of libjson-c-dev. The graphic interface was written with the help of the SDL library. <br/>


### &ensp;&ensp; <b> Technology  </b>
&ensp;&ensp;&ensp;&ensp; ● C <br/>
&ensp;&ensp;&ensp;&ensp; ● Cmake <br/>
&ensp;&ensp;&ensp;&ensp; ● SDL <br/>
&ensp;&ensp;&ensp;&ensp; ● libCurl <br/>
&ensp;&ensp;&ensp;&ensp; ● JSON <br/>
&ensp;&ensp;&ensp;&ensp; ● Odoo ERP system <br/>

---

---
## Photo
![Alt Text](https://github.com/Rock-Lex/Zeiterfassung/blob/master/data/media/5.png)

---
---

 ##  <b> How to install this project? </b>
   To install: <br/>
   - gcc/g++ <br/>
   - make <br/>
   - cmake <br/>
   - libsdl2-dev <br/>
   - libsdl2-image-dev <br/>
   - libsdl2-ttf-dev <br/>
   - libssl-dev <br/>
   - json <br/>
   - libjson-c-dev <br/>
   - x11 <br/>
   

## <b> How to run this project? </b>
 - git clone 
 - open project with Visual Studio
 - clear build folder with clear.sh
 - in build folder:
 &ensp; - cmake ..
 &ensp; - make
 &ensp; - ./Zeiterfassung

### <b> To Change  </b>
&ensp;&ensp;&ensp;&ensp; ● getScreenInfo.c       line 9 <br/>
&ensp;&ensp;&ensp;&ensp; ● odoo.c                ERP Links <br/>
&ensp;&ensp;&ensp;&ensp; ● render.h              images path<br/>
&ensp;&ensp;&ensp;&ensp; ● render.c              readScreenInfo()   - path<br/>

---


## Author

**Oleksandr Kamenskyi, 19 y.o, Berlin, Germany. Student - HWR Business Informatics**

---
---

## Video
[![Watch the video]()](https://drive.google.com/file/d/14mkv7EsXKtIX3N_zkCl5o68Lqo0G88ji/view?usp=sharing)


## Screenshots
![Alt Text](https://github.com/Rock-Lex/Zeiterfassung/blob/master/data/media/1.png)
---
![Alt Text](https://github.com/Rock-Lex/Zeiterfassung/blob/master/data/media/2.png)
---
![Alt Text](https://github.com/Rock-Lex/Zeiterfassung/blob/master/data/media/3.png)
---
![Alt Text](https://github.com/Rock-Lex/Zeiterfassung/blob/master/data/media/4.png)

---
---
