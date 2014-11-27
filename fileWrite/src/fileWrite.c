/*
 * Copyright (C) 2014 Gergely Molnar & Kalman Szabadi
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
* fileWrite
*/
#include <fileWrite.h>
#include <sys/stat.h>

int nullOrEmpty(const char *str){
    if (!(str && *str))
        return 1;

    return 0;
}


int fw_fod(const char *pathname){
    if(nullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        return 0;

    switch(st.st_mode & S_IFMT){
        case S_IFDIR:
            return 2; //directory
        break;

        case S_IFREG:
            return 1; //file
        break;

        default:
            return 0; //unkown
        break;
    }
}


int fw_exists(const char *pathname){
    if(nullOrEmpty(pathname))
        return 0;

    if(fw_fod(pathname) == 1 || fw_fod(pathname) == 2)
        return 1;

    return 0;
}


int fw_mkdir(const char *pathname){
    if(nullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        if(mkdir(pathname, 0777) != -1)
            return 1;

    return 0;
}


int fw_readOnly(const char *pathname){
    if(nullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        return 0;

    switch(st.st_mode & S_IRWXU){
        case S_IRUSR: //read only
            return 1;
        break;

        default:
            return 0;
        break;
    }
}


int fw_canWrite(const char *pathname){
    if(nullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        return 0;

    switch(st.st_mode & S_IWUSR){
        case S_IWUSR: //can write
            return 1;
        break;

        default:
            return 0;
        break;
    }
}


int fw_delete(const char *pathname){
    if(nullOrEmpty(pathname))
        return 0;

    switch(fw_fod(pathname)){
        case 1:
            if(unlink(pathname)!= -1)
                return 1;
        break;

        case 2:
            if(rmdir(pathname)!= -1)
                return 2;
        break;
    }

    return 0;
}
