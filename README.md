# qualFilme

O presente código tem a função de auxiliar na busca de filmes a partir de alguma informação dada sobre o mesmo.  

## A Estrutura de Dados

A estrutura é uma *Trie Existecial*.

Cada nodo da trie apresenta uma struct 'trieNode' a qual eh composta por um vetor dessa struct, sendo que cada posição do vetor representa um caracter que pode fazer parte do nome do filme.

A definição dos caracteres respectivamente com a posição no vetor foi feita através de macros com define.
Há o indC(c) o qual recebe um caracter e devolve qual deve ser a posição dele no vetor.
Há o indexToChar(i) o qual faz o oposto, recebe um indice que retorna qual o respectivo caracter desse indice.


## Lógica Geral

A partir de um nodo raiz, com seu vetor de caracteres, é realizada a inserção de filmes na trie, letra por letra.
Quando uma letra está sendo inserida, localiza-se a respectiva posição dela no vetor e nessa posição é criado outro nodo com o vetor.
Dessa forma, sabe-se que uma letra existe quando na posição dela há um nodo criado.

Além disso, a identificação do fim de uma palavra é feita através do caracter '\0' e segue a mesma lógica acima: quando estamos em um nodo e na posição respectiva do '\0' existe um nodo criado, significa que até aquela ponto da trie há uma palavra completa, porém, não necessariamente é o fim da trie. Pode haver outros nodos em outra posições do vetor que continuam progressivamente aumentando a palavra. Essa explicação exemplifica como essa estrutura de dados permite a visualização de prefixos nas palavras.


## Detalhe Padronização

No tipo de busca com curinga o código padronizaString não foi eficaz, visto que no caso de, por exemplo: "*four *funeral", retornar "?four ?funeral".
Podia-se apenas alterar o código para não colocar "?" no lugar de "." e "`*`", porém, não havia a certeza se poderia haver um filme com esses caracteres no cadastro.
Por isso, foi feito um código PadronizaCuringa no qual essa padronização é feita passando pelo nome do filme e separando as palavras (pulando quando aparece "." ou "`*`").
