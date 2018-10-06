#include "header.h"

//Inserto Tabla
tipoRet insertoTabla(tabla *tabl,string nombre){
    tabla tablon;
    tablon=*tabl;
    tablon=insertarTabla(tablon,nombre);

    *tabl=tablon;
    return ok;
}

tabla insertarTabla(tabla tabl, string name){
    //0 a null 1 a 0
    tabla nuevatabla;
    nuevatabla = new _tabla;

    nuevatabla -> nombre=name;
    nuevatabla -> ptrtabla=tabl; //1 -> null
    tabl=nuevatabla; // l -->32

    return tabl;
}

//Inserto columna

tipoRet insertoColumna(tabla *tabl, string name) {
    tabla newTab;
    newTab = *tabl;

    if (!esVacia(*tabl)) {
        newTab = insertarColumna(newTab, name);
    } else {
        return error;
    }

    *tabl = newTab;
    return ok;
}

tabla insertarColumna(tabla tabl, string name) {
    columna newCol;
    newCol = new _columna;
    newCol->nombreCol = name;

    if (esVacia(tabl->columna)) {
        tabl->columna = newCol;
    } else {
        columna colAux;
        colAux = new _columna;
        colAux = tabl->columna;

        newCol->sgtColumna = colAux;
        tabl->columna = newCol;
    }

    return tabl;
}


///Inicializar tabla
void creoTabla(tabla **tabl){

    tabla nuevatabla;
    nuevatabla = new _tabla;

    nuevatabla -> ptrtabla=NULL; //1 -> null
    **tabl = nuevatabla;
}

tipoRet inicioTabla(tabla *tabl){

    creoTabla(&tabl);

    return ok;
}


///Muestro Retorno
void muestroR(tipoRet resultado){

    switch(resultado){

    case 0 :
    cout << "ok";
    break;

    case 1:
    cout << "Error";
    break;

    case 2:
    cout << "No Implementado";
    break;

    }

}

bool esVacia(tabla tabl) {
    if(tabl == NULL || tabl->nombre == ""){
        return true;

    }else{
         return false;

    }
}

bool esVacia(columna column) {
    if(column == NULL || column->nombreCol == ""){
        return true;

    }else{
         return false;

    }
}

bool esVacia(fila aux) {
    if(aux == NULL){
        return true;

    }else{
         return false;

    }
}

tipoRet mostrarListaRet(tabla l){
    if(!esVacia(l)){
        mostrarListaRecur(l);
        return ok;
    }else{
        return error;
        cout << "Empty";
    }
}

void mostrarListaRecur(tabla l){
    columna col;
    col = new _columna;

    if (!esVacia(l)){

    // Escribe nombre de la tabla
        cout << endl;
        cout << "-----------------" << endl;
        cout << l->nombre << endl;
        cout << "-----------------" << endl;

    // Chequea cada columna
        col = l->columna;
        while(!esVacia(col)) {
            cout << " | " << col->nombreCol << " | ";
            col = col->sgtColumna;
        }
        cout << endl;
        cout << "-----------------" << endl;

    // Chequea la tabla siguiente
        mostrarListaRecur(l->ptrtabla); //recursiv

    // Finaliza
        cout << "Fin" << endl;

    } else{

    }
}


//Eliminar Tabla

tipoRet eliminoTabla(tabla *tabl,string nombre){

    //if tiene columnas pasar a eliminar las col primero
    tabla tablon;
    tablon=*tabl;
    if (!esVacia(tablon)){
        tablon=eliminarTabla(tablon,nombre);
        *tabl=tablon;
        return ok;
    }else{
        return error;
    }
}

tabla eliminarTabla(tabla tabl, string name){
    //0 a null 1 a 0
    tabla BorrarTabl;
    tabla anterior;

    BorrarTabl = new _tabla;
    anterior = new _tabla;

    anterior=NULL;
    BorrarTabl=tabl; //apunta al inicio de la lista

    while((BorrarTabl!=NULL)&&(BorrarTabl->nombre!=name)){ //mientras que BorrarTabl no sea null y no sea igual al nombre desdeado
        anterior=BorrarTabl; //anterior se iguala a BorrarTabl

        BorrarTabl=BorrarTabl->ptrtabla; //Borrartabl va al siguiente nodo 'Tabla'
    }

    //Casos cuando salga del while
    if(BorrarTabl==NULL){  // significa que recorrio toda la lista y cuando entro al while al final BorrarTabl es igual a null/ apunta al putero sig del ultimo nodo entonces NULL
        cout << "El elemento no existe";

    } else if(anterior==NULL) { // Si entra aca significa que no entro al while porque el elemento que buscamos es el primero en la lista, entonces  tabl apunta al sig nodo y deleteamos el primer nodo que esta en BorrarTabl.
        tabl = tabl->ptrtabla;
        delete BorrarTabl;

    } else { // El elemento esta en la lista pero no es el primero
        anterior->ptrtabla=BorrarTabl->ptrtabla;  // hacemos que el que estaba atras apunte al mismo que estaba apuntando borrartabl 'el siguiente del actual'
        delete BorrarTabl; // borramos borrartabl

    }

    return tabl;
}

