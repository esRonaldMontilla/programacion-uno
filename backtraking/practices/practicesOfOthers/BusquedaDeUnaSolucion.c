void buscar_una_solucion(paso: T){
    //inicializar alternativas
    while(alternativas && !solucion_encontrada){
        //obtener siguiente alternativa
        if(es_alternativa_valida){
            //almacenar_paso
            if(es_solucion){
                solucion_encontrada = 1;
                //procesar solucion
            }else{
                buscar_una_solucion(nuevo_paso);
                if(!solucion_encontrada){
                    //borrar paso
                }
            }
        }
    }
}