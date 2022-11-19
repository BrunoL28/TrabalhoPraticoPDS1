# TrabalhoPraticoPDS1

Trabalho Prático da Disciplina de Programação e Desenvolvimento de Software 1

O objetivo deste trabalho é fazer com que o aluno utilize as técnicas de programação aprendidas na disciplina
para desenvolver um jogo eletrônico gráfico semelhante a um jogo de tênis. A principal diferença é que, nesta
versão, os jogadores deverão jogar com diversas bolas ao mesmo tempo. Além disso, as paredes laterais são
sólidas, ou seja, se a bola bater em uma parede lateral, ela ricocheteia e volta para a quadra. O objetivo
dos jogadores é rebater as bolas de volta para o seu oponente. Um jogador ganha 1 ponto cada vez que
o oponente falhar em rebater uma bola. Para rebater uma bola, o jogador deve pressionar uma tecla (ex:
espaço). O jogo é de dois jogadores e cada jogador deve ter o seu conjunto de teclas de controle. Vence o
jogo aquele que fizer 10 pontos primeiro.
O jogo começa sem bolas em jogo. A cada 5 segundos, uma nova bola deve ser arremessada na quadra.
As bolas são arremessadas dos quatro cantos da quadra, começando pelo canto superior direito, depois pelo
superior esquerdo, depois pelo inferior esquerdo e depois pelo inferior direito. Lançamentos de bola devem
ocorrer sempre nessa ordem e só devem ser interrompidos quando o número de bolas na quadra atingir
um limite. Esse limite pode ser definido pelo aluno, mas deve ser, pelo menos, de 12 bolas. É importante
garantir também que o lançamento faça a bola cruzar a quadra em algum momento, mesmo que depois de
bater várias vezes nas paredes laterais. As bolas devem ter diferentes tamanhos, velocidades e devem ser
lançadas usando ângulos diferentes a cada lançamento.
Por fim, o seu jogo deve registrar o histórico (número de vitórias de cada jogador) das partidas realizadas
entre os jogadores. Para isso, armazene cada vitória (e derrota) em um arquivo. No final do jogo, esse
histórico deve ser exibido na tela, incluindo também o resultado da última partida que jogaram. Uma versão
básica desse jogo vem acompanha do kit de desenvolvimento Allegro disponível na página da disciplina.
