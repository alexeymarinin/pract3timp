# включить  < iostream >
# include  < строка >
# include  < cstdlib >  // exit ()
# include  < cstring >  // strpy ()
# include  < unistd.h >  // close ()
# включаем  < netinet / in.h >
# включить  < arpa / inet.h >
используя  пространство имен  std ;
void  Exception ( const string & why, const  int exitCode) // Исключения (возможные ошибки)
{
    cout << " ErrorCode: " << exitCode << endl << почему << endl;
    выход (exitCode);
}
int  main ()
{

    // структура с адресом нашей программы (клиента)
    sockaddr_in * selfAddr = новый (sockaddr_in);
    selfAddr-> sin_family = AF_INET; // интернет протокол IPv4
    selfAddr-> sin_port = 0 ;         // любой порт на усмотрение ОС
    selfAddr-> sin_addr . s_addr = 0 ;

    // структура с адресом "на той стороне" (сервера)
    sockaddr_in * remoteAddr = новый (sockaddr_in);
    remoteAddr-> sin_family = AF_INET;     // интернет протокол IPv4
    remoteAddr-> sin_port = htons ( 13 );  // порт 13
    remoteAddr-> sin_addr . s_addr = inet_addr ( « 82.179.90.12 » ); //   адрес

    // буфер для передачи и приема данных
    символ * буфер = новый  символ [ 4096 ];
    strcpy (buffer, « Скажите, пожалуйста, точную дату и время » );   // копируем строку
    int msgLen = strlen (буфер);      // вычисляем длину строки

    // создаём сокет
    int mySocket = сокет (AF_INET, SOCK_DGRAM, 0 ); // протокол udp
    if (mySocket == - 1 ) {
        закрыть (mySocket);
        Исключение ( « Ошибка открытого сокета » , 11 );
    }
    // связываем сокет с адрессом
    int rc = bind (mySocket, ( const sockaddr *) selfAddr, sizeof (sockaddr_in));
    if (rc == - 1 ) {
        закрыть (mySocket);
        Исключение ( « Ошибка привязки сокета с локальным адресом » , 12 );
    }

    // установливаем соединение
    rc = connect (mySocket, ( const sockaddr *) remoteAddr, sizeof (sockaddr_in));
    if (rc == - 1 ) {
        закрыть (mySocket);
        Исключение ( « Ошибка подключения сокета к удаленному серверу. » , 13 );
    }

    // передаём сообщение из буффера
    rc = отправить (mySocket, buffer, msgLen, 0 );
    if (rc == - 1 ) {
        закрыть (mySocket);
        Исключение ( « Сообщение об ошибке отправки » , 14 );
    }
    cout << " Отправляем: " << buffer << endl;

    // принимаем ответ в буффер
    rc = recv (mySocket, буфер, 4096 , 0 );
    if (rc == - 1 ) {
        закрыть (mySocket);
        Exception ( « Ошибка получения ответа. » , 15 );
    }
    буфер [rc] = ' \ 0 ' ; // конец принятой строки
    cout << " Получаем: " << buffer; // вывод полученного сообщения от сервера
    // закрыем сокет
    закрыть (mySocket);

    удалить selfAddr;
    удалить remoteAddr;
    удалить [] буфер;
    возврат  0 ;
}
