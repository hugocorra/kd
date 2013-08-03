cmake_minimum_required(VERSION 2.8)
Set(NEST_SOLUTION_FOLDERS True)
project("kd")

SET(BOOST_ROOT $ENV{BOOST_ROOT})
SET(Boost_USE_STATIC_LIBS ON) 

# procura pelos pacotes de acordo com o SO.
IF(CMAKE_SYSTEM_NAME MATCHES Windows)
    FIND_PACKAGE ( Boost REQUIRED )
ELSEIF(CMAKE_SYSTEM_NAME MATCHES Linux)
    FIND_PACKAGE ( Boost COMPONENTS filesystem system serialization REQUIRED )
ENDIF()

SET(Boost_DETAILED_FAILURE_MSG TRUE)

IF(Boost_FOUND)
    # seta diretórios de saída do modo debug e release.
    #SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG /Build/Debug)
    #SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE Build/Release)

    # diretórios de inclusão
    INCLUDE_DIRECTORIES($ENV{BOOST_ROOT})
    LINK_DIRECTORIES($ENV{BOOST_ROOT}/stage/lib)

    # diretórios com bibliotecas.

    #### NÃO ALTERAR AQUI O TIPO DE LINKAGEM, ALTERAR POR MEIO DO CCMAKE.
    SET (LIB_TYPE STATIC)
    ##################################################################

    # arquivos utilizados pelo prism
    FILE(GLOB SOURCES_CPP "src/*.cpp")
    FILE(GLOB SOURCES_H "src/*.hpp")
    LIST(APPEND SOURCES_SRC ${SOURCES_CPP} ${SOURCES_H})  

    IF(CMAKE_SYSTEM_NAME MATCHES Windows)
        ADD_DEFINITIONS("/wd4251 /wd4275 /MP") # desabilita alguns warning, habilita multiprocessamente 
    ELSEIF(CMAKE_SYSTEM_NAME MATCHES Linux)
        ADD_DEFINITIONS("-std=c++0x -fPIC -static -static-libstdc++ -Xlinker --whole-archive") # adiciona suporte ao c++ 0x e linkagem estatica
    ENDIF()

    ADD_EXECUTABLE(kd ${SOURCES_SRC})

    IF(CMAKE_SYSTEM_NAME MATCHES Windows)
      TARGET_LINK_LIBRARIES(kd ${Boost_LIBRARIES})
    ELSEIF(CMAKE_SYSTEM_NAME MATCHES Linux)
      TARGET_LINK_LIBRARIES(kd ${Boost_LIBRARIES} rt)
    ENDIF()
    
    # seta linguagem da biblioteca
    SET_TARGET_PROPERTIES(kd PROPERTIES LINKER_LANGUAGE CXX)
    set(EXECUTABLE_OUTPUT_PATH outputs)
    
    # arquivos utilizados pelo test
    FILE(GLOB TESTS_CPP "test-suite/*.cpp")
    FILE(GLOB TESTS_H "test-suite/*.hpp")
    LIST(APPEND TESTS_SRC ${TESTS_CPP} ${TESTS_H}) 
    
    # cria executável
    ADD_EXECUTABLE(test ${TESTS_SRC})
    SET_TARGET_PROPERTIES(test PROPERTIES LINKER_LANGUAGE CXX)
    
    # adiciona dependências
    TARGET_LINK_LIBRARIES(test ${Boost_LIBRARIES})      
    
    IF(CMAKE_SYSTEM_NAME MATCHES Linux) #TODO TENTAR REMOVER ESSA DEPENDENCIA
        TARGET_LINK_LIBRARIES(test pthread rt)
    ENDIF()
ENDIF()
