# Tourist Managing App
Tourist Managing App este o platformă interactivă dezvoltată în C++ pentru a facilita și eficientiza procesul prin care profesorii organizează excursii școlare la muzeu (cum ar fi Muzeul Grigore Antipa). Aplicația asigură o punte de comunicare directă între cadrele didactice și managementul muzeului.

La lansarea aplicației, utilizatorii se pot autentifica folosind două roluri principale: Administrator sau Utilizator.

1. Administrator 
Conectarea: accesul este restricționat și se face exclusiv pe baza unei parole de securitate predefinite în sistem (parola: Ghisoiu.Ioana).

Funcționalități principale:
  - Gestionarea cererilor: administratorul poate vizualiza toate cererile aflate în așteptare, trimise de către profesori.
  - Procesare și Aprobare: poate aproba programările noi; procesează cererile de ștergere a unor studenți din grup sau de anulare completă a vizitelor, sistemul recalculând automat taxele.
  - Filtrare și Raportare: poate afișa toate grupurile aprobate filtrate după o anumită dată calendaristică.
  - Interacțiune : poate administra și debloca echipamentele speciale ale muzeului (precum căștile VR pentru expozițiile interactive).
  - Export de date: poate genera și salva pe disc un raport financiar detaliat într-un fișier text (raport_vizite.txt), util pentru contabilitatea muzeului.


2. Utilizator (Profesorul)
Conectarea: accesul se face pe baza numelui, prenumelui și a unei parole generate automat (în formatul Nume.Prenume). Dacă profesorul se conectează pentru prima dată, aplicația îi creează automat un cont nou, cerându-i date precum vârsta, experiența și școala la care predă.

Funcționalități principale:
  - Explorarea ofertei: profesorul poate vizualiza detaliile muzeului și toate expozițiile disponibile (standard, temporare sau interactive), inclusiv tarifele acestora.
  - Programarea vizitei: poate iniția o cerere de programare pentru o vizită nouă, introducând data dorită, optând pentru un ghid și adăugând manual elevii participanți (cu datele lor personale și de studiu).
  - Modificarea componenței grupului: dacă un elev nu mai poate participa, profesorul poate trimite o cerere de anulare a biletului strict pentru acel elev.
  - Anulare completă: are opțiunea de a anula complet excursia, atâta timp cât respectă politica muzeului (anularea trebuie făcută cu cel puțin o zi înainte de data vizitei).
  - Sistem de Notificări: poate verifica în orice moment statusul programării sale și poate citi mesajele/notificările primite în inbox de la administrator (ex: confirmarea vizitei sau costul total calculat al grupului).    








