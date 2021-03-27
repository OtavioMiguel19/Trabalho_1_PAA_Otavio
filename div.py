def pardiv(x,partes):
    n=len(x)
    beg=min(x)[0] # menor valor da primeira coordenada
    end=max(x)[0] # maior valor da primeira coordenada
    ampl=float(end-beg) # diferença entre menor e maior valores
    ponto1=[] # lista que recebe os pontos do par mais próximo
    ponto2=[]
    distmin=10000000000000 # inicializar com distância muito grande
    for i in range(1,partes+1): # particionamento; 'partes' = número de subconjuntos
        end=min(x)[0]+(i*ampl/partes) # dividir a amplitude em subconjuntos igualmente espaçados
        part=[]
        for j in range(0,n): # define cada subconjunto 'part'
            if beg<=x[j][0]<=end:
                part.append(x[j])
        if bruto(part)[2]<distmin: # dentro de cada 'part', proceder por força bruta
            ponto1=bruto(part)[0]
            ponto2=bruto(part)[1]
            distmin=bruto(part)[2]
        cross=[]
        for k in range(0,n): # 'cruzamentos': a partir da divisão anterior, fazer força bruta para todos os pontos com distância menor que 'distmin' na primeira coordenada
            if end-distmin<=x[k][0]<=end+distmin:
                cross.append(x[k])
        if bruto(cross)[2]<distmin:
            ponto1=bruto(cross)[0]
            ponto2=bruto(cross)[1]
            distmin=bruto(cross)[2]
        beg=end # ir para o próximo subconjunto, repetir até chegar ao fim dos dados
    return(ponto1,ponto2,distmin)