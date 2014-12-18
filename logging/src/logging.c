/*
 * Copyright (C)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
logging
*/

#include <logging.h>
#include <fileWrite.h> //fwStringStream miatt!

int logging_out(int type, char * app_name, char * value){
    if(!app_name || !value){
        return 0; //NULL pointer vizsgálat
    }

    if(!*app_name || !*value){
        return 0; //Üres tartalomvizsgálat
    }

    struct FWStringStream *adatkezeles; //struct stringStream típusú változó dekraláció
    adatkezeles = fwssInit(1024); //inicializáljuk az adatkezeles változót (1024 db karaktert írhatunk bele)
    if(adatkezeles == NULL){
        return 0; //ha nem sikerult lefoglalni a kivant teruletet akkor NULL az eredmény és az nem jó!
    }

    char datum[100]; //deklaral datum char tömböt
    time_t now = time(NULL);//jelenlegi datum lekérdezéshez
    struct tm *t = localtime(&now);//jelenlegi datum lekérdezéshez


    strftime(datum, 100, "%d %m %Y %H:%M", t);//jelenlegi dátumon szöveggé alakít
    if(!fwssAddToBuffer(adatkezeles, datum, strlen(datum))){//jelenlegi dátum hozzáfűzése
        return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
    }
    if(!fwssAddToBuffer(adatkezeles, " | ", 3)){//space | space (3 karakter) elválasztas
        return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
    }
    switch(type){
        case 1:
            if(!fwssAddToBuffer(adatkezeles, "info", 4)){//hozzáfűzés típusa
                return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
            }
        break;

        case 2:
            if(!fwssAddToBuffer(adatkezeles, "warning", 7)){//hozzáfűzés típusa
                return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
            }
        break;

        case 3:
            if(!fwssAddToBuffer(adatkezeles, "error", 5)){//hozzáfűzés típusa
                return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
            }
        break;

        default:
            //üres (alapértelmezett ág)
        break;
    }
    if(!fwssAddToBuffer(adatkezeles, " | ", 3)){//space | space (3 karakter) elválasztas
        return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
    }
    if(fwssAddToBuffer(adatkezeles, app_name, strlen(app_name))){ //adatkezeleshez hozzaadjuk az alkalmazás nevét és a karaktereinek darabszámát
       return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
    }
    if(fwssAddToBuffer(adatkezeles, " | ", 3)){//space | space (3 karakter) elválasztas
       return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
    }
    if(fwssAddToBuffer(adatkezeles, value, strlen(value))){//hozzaadjuk az erteket/szoveget
       return 0; //ha a fuggveny 0-val tér vissza akkor nem sikerült a művelet
    }

    char fajlnev[128];//fajlnévnek
    strcpy(fajlnev, "/tmp/log/");//hozzad
    strcat(fajlnev, app_name);//hozzáfűz (magát a szöveget és a hosszát)
    strcat(fajlnev, ".log");//hozzáfűzés
    if(fwssWriteBuffer(adatkezeles, fajlnev, 1)){//végül hozzáfüzzük az {app_name}".log" fájlba mind (ha van tartalma akkor a végére)
        return 0;
    }

    fwssClose(adatkezeles);
    return 1;
}

