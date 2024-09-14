from random import randrange

class AFD:
    class TransicionNoneException(Exception):
        pass
    _alfabeto:list = [] # Lista de char/str
    _estados:list = [] # Lista de int
    _estado_ini:int = -1 # Int
    _estados_finales:list = [] # Lista de int
    _matriz:dict = {} # Hashmap<Integer,HashMap<Char, Integer>>

    def __init__(self, estados_finales:list, transiciones:list, estados:list = [], estado_ini:int = 0, alfabeto:list = ['a','b','c']) -> None:
        self.establecerQi(estado_ini = estado_ini)
        self.establecerQf(estados_finales = estados_finales)
        if (len(estados) == 0):
            self.cargarEstados()
        self._estados = estados
        self.cargarAlfabeto(alfabeto)
        self.cargarMatriz(transiciones=transiciones)

    # Getter _alfabeto
    def getAlfabeto(self) -> list:
        return self._alfabeto
    # Getter _estados
    def getEstados(self) -> list:
        return self._estados
    # Getter _estado_ini
    def getEstadoIni(self) -> int:
        return self._estado_ini
    # Getter _estados_finales
    def getEstadosFinales(self) -> list:
        return self._estados_finales
    # Getter _matriz
    def getMatriz(self) -> dict:
        return self._matriz

    # Setter _alfabeto
    def cargarAlfabeto(self, alfabeto:list) -> None:
        self._alfabeto = alfabeto
    # Setter _estados
    def cargarEstados(self) -> None: # Es aconsejable no usar ese método
        self._estados = [*range(self._estado_ini, max(self._estados_finales)+1)]
    # Setter _estado_ini
    def establecerQi(self, estado_ini:int) -> None:
        self._estado_ini = estado_ini
    # Setter _estados_finales
    def establecerQf(self, estados_finales:list) -> None:
        self._estados_finales = estados_finales

    def cargarMatriz(self, transiciones:list) -> None:
        contador:int = 0
        for i in self._estados:
            for char in self._alfabeto:
                # self._matriz[i][char]=transiciones[contador]
                self._matriz[(i,char)]=transiciones[contador]
                contador+=1

    def getSiguienteEstado(self, estado_actual:int, caracter:str) -> int: # Importante si devuelve un valor Nulo, entonces no existe ese estado/transicion
        return self._matriz[(estado_actual,caracter)]

    def isFinal(self, estado:int) ->bool:
        #return EstadosFinales.contatins(estado)
        if (estado in self._estados_finales):
            return True
        else:
            return False

class ME:
    _estado_actual:int = -1
    _afd:AFD = None

    def __init__(self, afd:AFD) -> None:
        self._afd = afd
        self._estado_actual= self._afd.getEstadoIni()

    def reset(self) -> None:
        self._estado_actual = self._afd.getEstadoIni()

    def acepta(self, caracter:str) -> None: # Sirve para comprobar que acepta el siguiente caracter a introducir.
        estado_tmp:int = self._afd.getSiguienteEstado(self._estado_actual, caracter=caracter)
        if estado_tmp != None:
            self._estado_actual= estado_tmp
        else:
            raise AFD.TransicionNoneException("Transición no encontrada, ERROR!!!")

    def isFinal(self) -> bool:
        return self._afd.isFinal(self._estado_actual)
    
    def compruebaCadena(self, cadena:str) -> bool:
        for index,i in enumerate(cadena):
            try:
                self.acepta(i)
                if (self.isFinal()) and (index==len(cadena)-1):
                    return True
            except: 
                return False

    def compruebaLista(self, lista:list) -> None:
        for palabra in lista:
            print("\t¿La palabra: "+palabra+ " es válida?" +(" Sí" if self.compruebaCadena(palabra) else " No"))
            self.reset()

    def obtenerCadenas(self, num_maximo:int = 100, lon_maxima:int = 10) -> list: # IMPORTANTE: Esto es cutre, lo sé, pero no sé cómo generarlo sin aleatoriedad. :(
        cadenas:list = []
        palabra:str = ""
        while (len(cadenas) != num_maximo):
            for i in range(randrange(0, lon_maxima)):
                palabra+="".join(self._afd._alfabeto[randrange(0,3)])

            if self.compruebaCadena(palabra) and not(palabra in cadenas):
                cadenas.append(palabra)
                print("\tEncontrada palabra válida: "+palabra)
            palabra = ""
            self.reset()
        return cadenas

def main():
    # me.acepta('b')
    # print("ca es válido? "+str(me.compruebaCadena("ca")))

    # Primera Expresión
    print("Primera Expresión:")
    afd = AFD(estados = [*range(1,7)], estados_finales = [5,6], estado_ini = 1, alfabeto= ['a','b','c'], transiciones=[2,3,None,None,4,None,5,None,6,None,None,6,None,None,None,6,None,None])
    me:ME = ME(afd = afd)
    listaprueba:list = ["ba","abc","abcaaaa","bc","bca", "ca","abk","aba","bcbc"]
    me.compruebaLista(lista=listaprueba)
    # me.obtenerCadenas()
    # Segunda Expresión
    print("Segunda Expresión:")
    afd = AFD(estados = [*range(1,9)], estados_finales = [6], estado_ini = 1, alfabeto= ['a','b','c'], transiciones=[None,2,3,4,None,5,6,None,None,4,None,3,None,7,None,None,None,None,None,None,8,6,7,None])
    me:ME = ME(afd = afd)
    listaprueba:list = ["bcbcbcbcbca","bcbbca","ca","cb","bca", "bcbca","baaaaaca","ba","bcbca"]
    me.compruebaLista(lista=listaprueba)
    me.obtenerCadenas()
    

if __name__ == "__main__":
    main()