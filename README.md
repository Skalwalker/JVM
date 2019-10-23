# JVM

A Java Virtual Machine é a pedra angular da plataforma Java. É o componente de tecnologia responsável por sua independência de hardware e sistema operacional, o pequeno tamanho de seu código compilado e sua capacidade de proteger os usuários de programas maliciosos.

A Java Virtual Machine é uma máquina de computação abstrata. Como uma máquina de computação real, ela possui um conjunto de instruções e lida com várias áreas da memória em tempo de execução. É razoavelmente comum implementar uma linguagem de programação usando uma máquina virtual.

## Instalação

A forma mais facil de realizar a instalação é com utilização do Makefile disponível.

Sem a utilização do Makefile a instalação pode ser feita com o seguinte comando.

```bash
$ g++ -std=c++11 -I include ./src/*.cpp -o ./bin/jvm
```

## Execução

Após a instalação será criado um arquivo executável _jvm_, dentro do diretório _bin_. Logo a execução deve ser realizada no diretório principal da JVM e ser chamado com _./bin/jvm_.

Para facilitar a execução de diversos arquivos _.class_, o executável utiliza dos atributos _argc_ e _argv_ realizando assim entradas por linha de comando. Por padrão, os arquivos _.class_ precisam estar dentro do diretório _test_examples_.

 **ARQUIVOS .class FORA DO test_examples NAO FUNCIONARÃO**.

## Exemplos de Execução:

```bash
$ ./bin/jvm HelloWorld.class
$ ./bin/jvm Exceptions.class
```
## Regras Gerais

* **Utilize o cppcheck ao programar**
* **Use enum sempre que possivel**
* **Não usar Switch**
* **Não usar goto**
* **Não use cores em print**
* **Não use bibliotecas de teste**
* **Não utiliza tipos padrões de C, apenas cstdint**

## Git Flow do Repositório

O Git Flow será um atributo de extrema importancia para o nosso repositório, evitando que _builds_ funcionais não sejam perdidas na implementação de novas _features_, bem como códigos estáveis não sejam quebrados.

### O que é um Git Flow?

Um Git Workflow, ou Git Flow é uma recomendação de como usar o Git para realizar o trabalho de maneira consistente e produtiva. Os fluxos de trabalho do Git incentivam os usuários a usar o Git de maneira efetiva e consistente. Dado o foco do Git em flexibilidade, não existe um processo padronizado de como interagir com o Git.

Ao trabalhar com uma equipe em um projeto gerenciado pelo Git, é importante garantir que a equipe esteja de acordo sobre como o fluxo de alterações será aplicado. Para garantir que a equipe esteja na mesma página, um fluxo de trabalho Git acordado deve ser desenvolvido ou selecionado.

### Descrição do nosso Git Flow

A Branch **dev** é a nossa branch principal e todos os merges requests devem ser feitos via Pull Request da branch feature que esta sendo desenvolvida para a dev. Quando uma versão da dev estiver usável, um Pull Request será submetido para a release.

## Desenvolvendo Novas Features

Novas funcionalidades devem ser desenvolvidas em branches únicas, **nenhuma feature deve ser desenvolvida na master e dev, nem na release**.

Então como desenvolvo novas features? Com novas branches!

O intuito é que cada biblioteca seja construida em uma branch única. Por exemplo, se eu quero criar uma função de girar 90 graus, devo criá-la em uma biblioteca de movimentação, logo essa biblioteca deve ser construida em uma branch nova.

O comando para criar uma nova branch é :

```git
git branch nome_da_branch
```

Para vizualisar todas as branches disponíveis:

```git
git branch
```

E para mudar seu ambiente de desenvolvimento para a branch desejada:
```git
git checkout nome_da_branch
````

Após ter adicionado mudanças e realizado o commit na sua branch, ao dar o push você pode se deparar com um possível erro. Este erro é porque sua branch ainda não existe no repositório remoto. Para corrigí-lo utilize o comando abaixo que realizará a ligação entre seu branch local e remoto.
````git
git push --set-upstream origin nome_da_branch
````

Quando todas as mudanças respectivas à branch estiverem prontas e testadas, solicite uma aprovação de pull request no repositório do Github.

## Modularização do Repositório

A modularização deve seguir esse [guia](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/)

## Documentação

Os comentários serão escritos com o propósito de se criar um [Doxygen](http://www.doxygen.nl/manual/docblocks.html)

Utilize apenas o seguinte formato para comentário Doxygen:
```c
/**
 * ... text ...
 */
 ```

 E para explicações _inline_ que não irão para a documentação:
 ```c
 // Text
 ```
