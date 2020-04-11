# Penjelasan dan Penyelesaian Soal Shift 3 Sistem Operasi
disusun oleh: M. Mikail Dwi Khusnanda (028) & Ghifari Akbar R (040)


# Soal Nomer 1 Pokezone
<h2>1. Penjelasan</h2>
pada pokezone terdapat fitur
<ul>
  <li>penyediaan pokemon (random)</li>
  <li>catch pokemon (shared memory dari flag traizone)</li>
  <li>restock barang shop</li>
  <li>shutdown</li>
</ul>
penyediaan pokemon hanya berupa ID dari pokemon dimana 123: 1 adalah jenis pokemon, 2 adalah rarity pokemon, 3 adalah shiny atau tidak<br>
contoh: 130 -> pokemon no 1 di rarity ke 3 dan 0 artinya tidak shiny

<h2>2. Penyelesaian</h2>
<p>dalam kodingan pertama membuat shared memory yang dibutuhkan, dengan key. lalu membuat child process untuk membuat restock dari shop dengan kodingan:

```c
    pid_t mainfeature;


    mainfeature = fork();
    if(mainfeature==0){
      while(1){
        if(*lp <= 190){*lp+=10;}
        else{*lp=200;}

        if(*pokeball<=190){*pokeball+=10;}
        else{*pokeball=200;}

        if(*berry<=190){*berry+=10;}
        else{*berry=200;}
        sleep(10);
      }
    }
```

lalu membuat loop untuk mengecek apakah capture mode sudah dimulai, jika belum maka looping lagi.

```c
    while(1){
          pthread_create( &tid[0], NULL, &pokemon, NULL);
          pthread_create( &tid[1], NULL, &pokemon, NULL);
          pthread_join(tid[0],NULL);
          pthread_join(tid[1],NULL);
          *pokesm = hasil;
          if(*cmsm == 1){
            printf("Combat mode activated\n" );
            int st = 0;
            while(*status == 0){
              st = (rand() % 100) + 1;
              if(st <= esrate && *status == 0){*status=2;}
              if(*status==0){sleep(20);}
            }
            if(*status == 1){
            printf("pokemon telah ditangkap\n" );
            }
            else{
              printf("pokemon kaburr\n" );
            }
            *cmsm = 0;*status = 0;
          }
          pthread_create(&tid[5],NULL,&capture,NULL);
        printf("%d\n", hasil);

        hasil = 0;cpoke = 0;enrate=0;esrate=0;caprate=0;dolrate=0;
        sleep(1);
      }
```

<h2>Kesulitan</h2>
karena program nya saling berhubungan saya kesulitan mana yang diselesaikan dahulu, sedangkan meskipun tidak ada error bukan berarti programnya dapat berjalan, harus selesai kedua program agar dapat dibuktikan bahwa tidak ada misscode dalam kodingan saya.

# Soal Nomor 1 Traizone
<h2>1. Penjelasan</h2>
pada traizone, ia menyediakan fitur:
<ul>
  <li>cari pokemon</li>
  <li>pokedex</li>
  <li>shop</li>
  <li>capture mode
    <ul>
      <li>capture</li>
      <li>item</li>
      <li>kabur</li>
    </ul>
  </li>
  <li>shutdown</li>
</ul>

<h2>2. Penyelesaian</h2>
pertama membuat shared memory untuk konek dengan pokezone

```c
key_t pokek = 1111;
  key_t capk  = 1112;
  key_t shtk  = 3333;
  key_t cmk   = 4444;
  key_t ulpk  = 5555;
  key_t lpk   = 6666;
  key_t pokk  = 7777;
  key_t berk  = 8888;
  key_t statk = 9999;


  int pshmid = shmget(pokek,  sizeof(int), IPC_CREAT | 0666);
  int shtshmid = shmget(shtk, sizeof(int), IPC_CREAT | 0666);
  int cmshmid = shmget(cmk  , sizeof(int), IPC_CREAT | 0666);
  int ulpshmid = shmget(ulpk, sizeof(int), IPC_CREAT | 0666);
  int lpshmid = shmget(lpk  , sizeof(int), IPC_CREAT | 0666);
  int pokshmid = shmget(pokk, sizeof(int), IPC_CREAT | 0666);
  int bershmid = shmget(berk, sizeof(int), IPC_CREAT | 0666);
  int sttshmid = shmget(statk, sizeof(int), IPC_CREAT| 0666);
  int capshmid = shmget(capk, sizeof(int), IPC_CREAT | 0666);

  pokesm = shmat(pshmid,    NULL, 0);
  shutsm = shmat(shtshmid,  NULL, 0);
  cmsm = shmat(cmshmid,     NULL, 0);
  ulpsm = shmat(ulpshmid,   NULL, 0);
  lp = shmat(lpshmid,       NULL, 0);
  pokeball = shmat(pokshmid,NULL, 0);
  berry = shmat(bershmid,   NULL, 0);
  status = shmat(sttshmid,  NULL, 0);
  captur = shmat(capshmid,  NULL, 0);
  ```
lalu membuat random seed agar beda tiap membuka terminal, lalu membuat thread looping pengurangan AP lalu membuat switch dan menampilkan menu. dengan opsi 1. cari pokemon, 2. pokedex, 3. shop, dan yang terakhir adalah exit flag.

```c
int pilgan2=0;
  while(pilihan != 5){
    pilgan2=0;
    pthread_create(&tid[0],NULL,&menu,NULL);
    pthread_join(tid[0],NULL);
    scanf("%d", &pilihan);
    if(carpok==1 && pilihan!=1){
      pthread_join(tid[2],NULL);
      printf("ketemu!\n" );
    }
    switch (pilihan) {
      case 1:
        printf("disini jalan\n");
        sleep(1);
        if(carpok==0){
        carpok = 1;
        pthread_create(&tid[1],NULL,&menu,NULL);
        pthread_join(tid[1],NULL);
        pthread_create(&tid[2],NULL,&cari_pokemon,NULL);
        }
        else if(carpok==1){
          carpok=0;
          pthread_join(tid[2],NULL);
          pthread_create(&tid[4],NULL,&menu,NULL);
          pthread_join(tid[4],NULL);
        }
        break;
      case 2:
        pthread_create(&tid[5],NULL,&pokedex,NULL);
        pthread_join(tid[5],NULL);
        break;
      case 3:
        while(pilgan2!=4){
          pthread_create(&tid[8],NULL,&shop,NULL);
          pthread_join(tid[8],NULL);
          scanf("%d", &pilgan2);
          switch (pilgan2) {
            case 1:
              //5
              if(dollar<5){
                strcat(message,"uang tidak cukup");
                message1++;
              }
              else{
                dollar-=5;
                item[0]++;
                dump = *pokeball;
                dump--;
                *pokeball = dump;
              }
              break;
            case 2:
              if(dollar<60){
                strcat(message,"uang tidak cukup");
                message1++;
              }
              else{
                dollar-=60;
                item[1]++;
                dump = *lp;
                dump--;
                *lp = dump;
              }
              break;
            case 3:
              if(dollar<15){
                strcat(message,"uang tidak cukup");
                message1++;
              }
              else{
                dollar-=15;
                item[2]++;
                dump = *berry;
                dump--;
                *berry = dump;
              }
              break;
          }
        }
        break;
      case 4:
        *cmsm = 1;
        if(cetekan==1){
          while(pilihan2!=3 && *cmsm==1){
            pthread_create(&tid[6],NULL,&menu2,NULL);
            pthread_join(tid[6],NULL);
            scanf("%d", &pilihan2);
            switch(pilihan2){
              case 1:
                if(item[1]<=0){printf("anda tidak memiliki pokeball\n" );break;}
                else{
                  item[1] -= 1;
                  *captur=pokeid;
                  sleep(3);
                  if(*captur == 0){
                    strcat(message,"Pokemon lepas dari pokeball\n");
                    message1 =1;
                    *cmsm=0;
                    break;
                  }
                  else if(*captur == 999){
                    strcat(message, "pokemon telah ditangkap");
                    pokmon[jmlh_poke] = dolpok;
                    message1 = 1;
                    *cmsm = 0;
                    if(jmlh_poke==6){
                      strcat(npoke7,nama);
                      ap[6] = 100;
                    }
                    else if(jmlh_poke==5){
                      strcat(npoke6,nama);
                      ap[5]=100;
                    }
                    else if(jmlh_poke==4){
                      strcat(npoke5,nama);
                      ap[4] = 100;
                    }
                    else if(jmlh_poke==3){
                      strcat(npoke4,nama);
                      ap[3]=100;
                    }
                    else if(jmlh_poke==2){
                      strcat(npoke3,nama);
                      ap[2] = 100;
                    }
                    else if(jmlh_poke==1){
                      strcat(npoke2,nama);
                      ap[1]=100;
                    }
                    else if(jmlh_poke==0){
                      strcat(npoke1,nama);
                      ap[0] = 100;
                    }
                    else{
                      strcat(message,"Pokemon dilepas\n");
                      message1 = 1;
                      dollar+=dolpok;
                    }
                    jmlh_poke++;
                    break;
                  }
                }
                break;
              case 2:
                *ulpsm = 1;
                break;
              case 3:
                *cmsm = 0;
                break;
              case 4:
                //exit(EXIT_SUCCESS);
                break;
            }
        }
        cetekan=0;
        break;
        }
        else{
          printf("maaf anda harus mencari pokemon terlebih dulu nub\n" );
          break;
        }
    case 5:
      *shutsm=1;
      sleep(5);
      shutdown();
      exit(EXIT_SUCCESS);
      break;
    }
  }
```

<h2>Source</h2>
https://www.geeksforgeeks.org/multithreading-c-2/ <br>
https://www.tutorialspoint.com/multithreading-in-c <br>
https://www.thegeekstuff.com/2012/04/terminate-c-thread/ <br>
https://www.geeksforgeeks.org/ipc-shared-memory/ <br>
https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_shared_memory.htm <br>

# Soal Nomor 2
<h2>1. Penjelasan</h2>
membuat games taptap yang menggunakan server dan client.

<h2>2. Penyelesaian</h2>
saya menggunakan ncurses pada library sebagai alternatif dalam mengubah terminal dari cooked menjadi raw. lalu melakukan show menu biasa dan switch biasa.

<h2>Kesulitan</h2>
saya belum menemukan cara untuk melakukan client server jika client lebih dari satu, telah mencoba membuat multisocket tetapi tetap sampai akhir belum ketemu caranya

<h2>Source</h2>
https://www.youtube.com/watch?v=BIJGSQEipEE
https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
https://stackoverflow.com/questions/13669474/multiclient-server-using-fork
https://github.com/nikhilroxtomar/Multiple-Client-Server-Program-in-C-using-fork


# Soal Nomor 3
<h2>1. Penjelasan</h2>
<p>mengkategorikan file dalam bentuk extension yang dimiliki dalam suatu folder. contohnya jika ada file yang berupa .txt dan .jpeg maka membuat folder baru bernama txt dan jpeg dan berisikan file masing masing dalam folder itu</p>

<h2>Penyelesaian</h2>

<p> dua fungsi move_file dan mk_directory untuk memindahkan dan membuat folder</p>
```static void move_file(const char *filename)
{

    char *dot = strrchr(filename, '.');
    
    mk_directory(dot + 1);

    size_t namelen = strlen(dot + 1) + strlen(filename) + sizeof("/");

    char *buffer = malloc(namelen);

    sprintf(buffer, "%s/%s", dot + 1, filename);

    rename(filename, buffer);

    free(buffer);
}


static void mk_directory(const char *dirname)
{

	char *dot = strrchr(dirname, '.');

   	mkdir(dirname, 0755);
    
}
```


<h2>Kesulitan</h2>
<p>menentukan fungsi dan cara mengkategorikan dan memindahkan file ke folder tertentu, dan memastikan /* dapat berjalan dan mengkategorikan semua file <p>
	

<h2>Source</h2>
https://www.geeksforgeeks.org/multithreading-c-2/ <br>
https://www.tutorialspoint.com/multithreading-in-c <br>
https://www.thegeekstuff.com/2012/04/terminate-c-thread/ <br>
https://www.geeksforgeeks.org/ipc-shared-memory/ <br>
https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_shared_memory.htm <br>

# Soal Nomor 4
<h2>1. Penjelasan</h2>
pada A, menampilkan perkalian matrix biasa
pada b, menampilkan matriks dari A tetapi dengan perubahan faktorial
pada c, melakukan pipe untuk mencari nomer 3 dari file

<h2>Penyelesaian</h2>
pada soal A cukup jelas dengan menggunakan penampilan perkalian matriks, soal B karena membutuhkan matriks A, maka matriks A ditambahkan pada bawahnya agar dapat menciptakan shared memory, lalu selain itu sama, cuma beda dalam cara mencari faktorial, lalu pada soal C, menampilkan pipe yang sama dengan

```bash
ls | wc -l
```
menggunakan dup2 agar dapat menyimpan hasil dari execv.

<h2>Kesulitan</h2>
kesulitan terdapat pada nomor 4b dimana kebingungan terjadi ketika harus mengirimkan data berupa array, yang akhirnya menggunakan memcpy
