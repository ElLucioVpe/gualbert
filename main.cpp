#include "header.h"

int main()
{

    string entradaUsuario;

    int varCount = 0;
    string var1;
    string var2;
    string var3;
    string var4;
    string var5;

    tabla tabl = new _tabla;
    muestroR(inicioTabla(&tabl));

    //muestroR(insertoTablaAbb(tabl,"clientes"));

    muestroR(insertoTablaAbb(tabl,"Hoteles"));

    muestroR(insertoTablaAbb(tabl,"personas"));
    muestroR(insertoTablaAbb(tabl,"mascotas"));
    muestroR(insertoTablaAbb(tabl,"prueba"));

    //tabl = retornarTablaBusacada(tabl,"clientes" );
    muestroR(insertoColumna(&tabl, "mascotas", "nombre"));
    muestroR(insertoColumna(&tabl, "mascotas", "edad"));
    muestroR(insertoColumna(&tabl, "mascotas", "tipo"));
    muestroR(insertoColumna(&tabl, "prueba", "xd"));
    muestroR(insertoColumna(&tabl, "prueba", "NDEAAAA"));

    muestroR(insertoColumna(&tabl, "mascotas", "estaVivaNDAH"));
    muestroR(insertoDato(&tabl, "mascotas", "julian:18:agua:0"));

    muestroR(insertoDato(&tabl, "prueba", "0:xdxd"));
    muestroR(insertoDato(&tabl, "prueba", "1:lmao"));
    muestroR(insertoDato(&tabl, "prueba", "2:nibba"));
    muestroR(insertoDato(&tabl, "prueba", "3:rigby"));

    //muestroR(insertoDato(&tabl, "mascotas", "schrodinger:50:tramboliko:0"));
    muestroR(proyectarWhere(&tabl, "prueba", "xd<1", "mascotas2.0"));


    //columna colAAAH = retornarColumna(&tabl, "mascotas", "tipo");
    //cout << "FJKJDKSJKSA " << colAAAH->nombreCol << endl;

    //muestroR(eliminoTabla(&tabl, "clientes"));
    //muestroR(eliminoColumna(&tabl, "personas", "ci"));

    //muestroR(eliminoTabla(&tabl, "personas
    //muestroR(proyectoTabla(&tabl, "mascotas", "nombre:edad", "mascotas2.0"));

    //muestroR(eliminoColumna(&tabl, "clientes", "ci"));

    //tabla tabRet = retornarTablaBusacada(tabl, "mascotas2.0");
    //cout << "adnaskjds" << tabRet->columna->nombreCol << endl;

    mostrarSim(tabl);

    ///Probar FUNCS
    /*
    muestroR(inicioTabla(&tabl));
    muestroR(insertoTabla(&tabl,"clientes"));
    muestroR(insertoColumna(&tabl, "clientes", "ci"));
    muestroR(insertoColumna(&tabl, "clientes", "Nombre"));
    muestroR(insertoColumna(&tabl, "clientes", "Apellido"));
    muestroR(insertoDato(&tabl,"clientes", "adrian:Diego1:RICA"));
    muestroR(insertoDato(&tabl,"clientes", "2:Diego2:NoSE"));
    muestroR(insertoDato(&tabl,"clientes", "3:Nicolas:SISI"));
    muestroR(insertoDato(&tabl,"clientes", "4:Xd:SISI"));
    muestroR(insertoDato(&tabl,"clientes", "5:siete:SISI"));
    muestroR(insertoDato(&tabl,"clientes", "6:ocho:SISI"));
     muestroR(insertoDato(&tabl,"clientes", "7:UFFF:SISI"));
    muestroR(insertoDato(&tabl,"clientes", "8:dos:SISI"));
    muestroR(insertoDato(&tabl,"clientes", "10:NIc:SISI"));
     muestroR(insertoDato(&tabl,"clientes", "11:NIc:SISI"));
     muestroR(insertoDato(&tabl,"clientes", "13:NIc:SISI"));
     muestroR(insertoDato(&tabl,"clientes", "12:NIc:SISI"));
     muestroR(insertoDato(&tabl,"clientes", "9:Rodri:SISI"));
    muestroR(muestroTabla(tabl,"clientes"));
    //LUCIUS SEMPAI
    */
    ///

    do {
        cout << "mahSQL> ";

        string orden;
        std::getline(std::cin, entradaUsuario);

        if (entradaUsuario.empty())
        {
            cout << entradaUsuario;
        } else if (entradaUsuario == "salir") {
            break;
        } else {

            varCount = 0;
            std::istringstream dd(entradaUsuario);
            std::string token;

            //Verifico numero de datos que se quieren insertar
             while(std::getline(dd, token, '(')) {

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

            if(orden == "ayuda") {
                cout << endl;
                cout << "-------------------------------------" << endl;
                cout << "mahSQL by Luis Pagola y Luciano Porta" << endl;
                cout << "-------------------------------------" << endl;
                cout << endl;
                cout << "Funciones disponibles:" << endl;
                cout << endl;
                cout << "- iniciarTabla()" << endl;
                cout << "- insertarTabla(nombreTabla)" << endl;
                cout << "- agregarColumna(nombreTabla,nombreColumna)" << endl;
                cout << "- eliminoColumna(nombreTabla,nombreColumna)" << endl;
                cout << "- insertoDato(nombreTabla,dato1:dato2)" << endl;
                cout << "- eliminoDato(nombreTabla,columna,fila)" << endl;
                cout << "     ej.: eliminoDato(clientes,personas,pepe)" << endl;
                cout << "- eliminoDatoTupla(nombreTabla,nombreColumna,condicion)" << endl;
                cout << "     eliminoDatoTupla puede comparar =, > o <." << endl;
                cout << "     eliminoDatoTupla puede utilizar * al comparar strings." << endl;
                cout << "     ej.: eliminoDatoTupla(clientes,nombre=pep*)" << endl;
                cout << "- actualizoDatos(nombreTabla,condicionColumna,condicionDato,nuevoDatoCol,nuevoDato)" << endl;
                cout << "- printDataTable(nombreTabla)" << endl;
                cout << "- mostrarTablas()" << endl;
                cout << endl;
            } else {

                //cout << orden << endl;

                if(orden == "iniciarTabla") {
                    muestroR(inicioTabla(&tabl));
                } else if (orden == "insertarTabla") {
                    muestroR(insertoTabla(&tabl,var1));
                } else if (orden == "agregarColumna") {
                    muestroR(insertoColumna(&tabl, var1, var2));
                } else if (orden == "eliminoColumna") {
                    muestroR(eliminoColumna(&tabl, var1, var2));
                }  else if (orden == "insertoDato") {
                    muestroR(insertoDato(&tabl, var1, var2));
                } else if (orden == "eliminoDato") {
                    muestroR(eliminoDato(&tabl, var1, var2, var3));
                } else if (orden == "actualizoDatos") {
                    muestroR(actualizoDatos(&tabl, var1, var2, var3, var4, var5));
                } else if (orden == "printDataTable") {
                    muestroR(muestroTabla(tabl,var1));
                } else if (orden == "eliminoDatoTupla") {
                    muestroR(eliminoDatoTupla(&tabl, var1, var2));
                } else if (orden == "mostrarTablas") {
                    muestroR(mostrarListaRet(tabl));
                } else {
                    cout << "Comando no valido. Puede escribir ayuda para repasar los comandos basicos." << endl;
                }

                //cout << "ORDEN: " << orden << " VAR1: " << var1 << " VAR2: " << var2 << " VAR3: " << var3 << " VAR4: " << var4 << " VAR5: " << var5 << endl;
                var1 = "";
                var2 = "";
                var3 = "";
                var4 = "";
                var5 = "";

                //cout << orden << endl;
            }
        }
    } while (entradaUsuario != "salir");

    cout << "Hasta luego!" << endl;
    return 0;
}
