# UFRN - Projeto da disciplina de ITP - 2020.2 

O projeto da disciplina de ITP do semestre de 2020.2 consiste em criar um bot para jogar Buraco [(link do repositório do projeto)](https://github.com/amccampos/itp-prj-2020.2). A atividade foi dividade em duas partes, um bot simples e um bot avançado. Aqui irei descrever a funcionamento de cada um deles e como eu os desenvolvi.


- [Bot Simples](#Bot-Simples)
- [Bot Avançado](#Bot-Avançado)



# Bot Simples
O bot mais básico tem as seguintes funcionalidades:

1. **Puxar uma carta**: Verifique se a carta que seu adversário descartou forma jogo com as cartas que tem na mão. Se formar, pegue o lixo formando o jogo. Se não, puxe uma do deque de compras.
3. **Forma Jogos**:  Verifique se cartas da mão encaixa em algum jogo já baixado. Enquanto existir adicione as cartas no jogo.
2. **Descartar uma carta**: Busque a carta da mão que esteja o mais longe de um possível jogo. 

# Bot Avançado
1. Get discard usando mele
2. Meld new usando mele
3. Implementar "pior_carta" para levar em consideração possíveis jogos do lixo.
4. Struct com vetor e tamanho (opcional).

- Vale mais a pena puxar ou pegar o morto ?
Var : minhas cartas,meus jogos, jogos inimigos,lixo, quantas cartas faltam p acabar
    - Ver se quais jogos faço com  o lixo
    - Se eu consigo pegar ele depois


--Baixar os jogos apenas quando estiver com toda mão completa ou o baralho estiver prestes a acabar--
- Sempre que possível pegar o morto, pegar com melé quando a probabilidade do inimigo conseguir pegar todo morto for maior que a probabilidade de eu pegar no prox round.
- Caso tenha uma canastra completa, descartar cartas extras caso necessário.
- Descarta carta com menor probabilidade do inimigo fazer jogo e que não seja essencial em um jogo formado por mim e que não quebra a sequência de uma canastra.
Para funcionar é necessário:
    Saber todas conhecidas (minha mão + meus jogos feitos + lixo + jogos inimigos feitos)
    Saber as cartas deconhecidas (baralho + mão inimiga)

### Objetivos dados pelo prof
1 - Get discard usando mele
2 - Meld new usando mele
3 - Implementar "pior_carta" para levar em consideração possíveis jogos do lixo.
4- Struct com vetor e tamanho (opcional).

### To do
- Ajeitar primeira parte jogar_lixo;
Util colocar no readme
https://www.youtube.com/watch?v=KVlGx-9CuO4&ab_channel=Programa%C3%A7%C3%A3oDin%C3%A2mica
