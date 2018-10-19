#include "header.h"

int main()
{

    string orden;

    int varCount = 0;
    string var1;
    string var2;
    string var3;
    string var4;
    string var5;

    tabla tabl = new _tabla;

    do {
        cout << "mahSQL> ";
        cin >> orden;

        varCount = 0;
        std::istringstream dd(orden);
        std::string token;

        //Verifico numero de datos que se quieren insertar
         while(std::getline(dd, token, '(')) {
            if(orden.empty()) {
                cout << "xd";
                break;
            }

            std::istringstream dd(token);
            std::string token2;
            if(varCount == 0) {
                orden = token;
                varCount++;
            } else {
                //cout << "token1: " << token << endl;
                while(std::getline(dd, token2, ',')) {

                    //cout << "token2: " << token2 << "lvl: " << varCount << endl;

                    switch (varCount) {
                        case 1:
                            var1 = token2;
                            break;
                        case 2:
                            var2 = token2;
                            break;
                        case 3:
                            var3 = token2;
                            break;
                        case 4:
                            var4 = token2;
                            break;
                        case 5:
                            var5 = token2.substr(0, token2.size()-1);
                            break;
                    }
                    varCount++;
                }
            }
        }

        varCount--;
        //cout << "level: " << varCount << endl;
        if(varCount != 5) {
            switch(varCount) {
                case 1:
                    var1 = var1.substr(0, var1.size()-1);
                    break;
                case 2:
                    var2 = var2.substr(0, var2.size()-1);
                    break;
                case 3:
                    var3 = var3.substr(0, var3.size()-1);
                    break;
                case 4:
                    var4 = var4.substr(0, var4.size()-1);
                    break;
            }
        }

        //cout << orden << endl;

        if(orden == "iniciarTabla") {
            muestroR(inicioTabla(&tabl));
        } else if (orden == "insertarTabla") {
            //cout << var1 << endl;
            muestroR(insertoTabla(&tabl,var1));
        } else if (orden == "agregarColumna") {
            muestroR(insertoColumna(&tabl, var1, var2));
        } else if (orden == "eliminoColumna") { ////////////////
            muestroR(eliminoColumna(&tabl, var1, var2));
        }  else if (orden == "insertoDato") {
            muestroR(insertoDato(&tabl, var1, var2));
        } else if (orden == "eliminoDato") {
            muestroR(eliminoDato(&tabl, var1, var2, var3));
        } else if (orden == "actualizoDatos") {
            muestroR(actualizoDatos(&tabl, var1, var2, var3, var4, var5));
        }

        //cout << "ORDEN: " << orden << " VAR1: " << var1 << " VAR2: " << var2 << " VAR3: " << var3 << " VAR4: " << var4 << " VAR5: " << var5 << endl;
        var1 = "";
        var2 = "";
        var3 = "";
        var4 = "";
        var5 = "";


    } while (orden != "Salir");

    cout << "Bye!" << endl;
    return 0;
}
