nombres = [] 
ataques = []
defensas = []

def calDefensa(x): # toma una respuesta y si es válida, calcula su defensa total, si no devuelve -infinito 
    if len(x[1]) != 5:
        count = -1
    else:
        count = 0
        for i in x[1]:
            count += defensas[i]
    return count

def calAtaque(x): # toma una respuesta y si es válida, calcula su ataque total, si no devuelve -infinito 
    if len(x[0]) != 5:
        count = -1
    else:
        count = 0
        for i in x[0]:
            count += ataques[i]
    return count

def mejorOrdenAlf(x,y): # toma dos respuesta válidas y devuelve la que mejor orden lexicográfico tenga
    nombresx = []
    nombresy = []
    for i in x[0]:
        nombresx.append(nombres[i])
    for j in y[0]:
        nombresy.append(nombres[j])
    xAtaqOrdenado = sorted(nombresx)
    yAtaqOrdenado = sorted(nombresy)
    decidido = False
    i = 0
    mejor = x
    while not decidido:
        if i == 5:
            decidido = True
        else:
            if xAtaqOrdenado[i] < yAtaqOrdenado[i]:
                decidido = True
            elif xAtaqOrdenado[i] > yAtaqOrdenado[i]:
                decidido = True
                mejor = y
            else:
                i += 1
    return mejor

def mejorDefensa(x,y): # toma dos respuestas y devuelve la que tenga mayor defensa tenga
    valorDefensax = calDefensa(x)
    valorDefensay = calDefensa(y)
    if valorDefensax == -1:
        return y
    if valorDefensax == valorDefensay:
        return mejorOrdenAlf(x,y)
    elif valorDefensax > valorDefensay:
        return x
    else:
        return y

def mejorAtaque(x,y): # toma dos respuestas y devuelve la que tenga mayor ataque tenga
    valorAtaquex = calAtaque(x)
    valorAtaquey = calAtaque(y)
    if valorAtaquex == -1:
        return y
    if valorAtaquex == valorAtaquey:
        return mejorDefensa(x,y)
    elif valorAtaquex > valorAtaquey:
        return x
    else:
        return y

def maximizarAtaque(i, ataque, defensa): # función principal recursiva de backtracking que devuelve la formación óptima, con ataque maximizado
    if len(ataque) > 5 or len(defensa) > 5:    # poda, hay más de 5 jugadores por grupo
        return [],[]
    elif i == 10:  # caso base, llegó a una hoja del árbol
        return ataque.copy(), defensa.copy()
    else:
        ataque.append(i)
        x = maximizarAtaque(i+1, ataque, defensa)     # el jugador i va a atacar
        ataque.remove(i)
        defensa.append(i)
        y = maximizarAtaque(i+1, ataque, defensa)     # el jugador i va a defender
        defensa.remove(i)
        return mejorAtaque(x,y) 

def main():
    
    T = int(input())  # Entero que indica la cantidad de casos
    global nombres
    global ataques
    global defensas
    casos = []
    for i in range(T):
        nombres = []   
        ataques = []
        defensas = []
        for j in range(10): # Input
            nombrej, ataquej, defensaj = input().split()
            nombres.append(nombrej)
            ataques.append(int(ataquej))
            defensas.append(int(defensaj))
        
        ataque, defensa = maximizarAtaque(0, [], []) # backtracking

        atacantes = []
        defensores = []
        for k1 in ataque:
            atacantes.append(nombres[k1])
        for k2 in defensa:
            defensores.append(nombres[k2])
        casos.append(atacantes)
        casos.append(defensores)

    for m in range(T): # Output
        print('Case {}:'.format(m+1)) 
        atacantes = ', '.join(tuple(sorted(casos[0])))
        defensores = ', '.join(tuple(sorted(casos[1])))
        print('({})'.format(atacantes))
        print('({})'.format(defensores))
        casos = casos[2:]
     

if __name__ == "__main__":
    main()
