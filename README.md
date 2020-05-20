# README
# WAZNE
Żeby zbudować projekt z wyświetlaniem punktów trzeba dopisać do CMakeLists.txt to: (zamień nazwa_projektu na swoją)
````
target_link_libraries(Nazwa_projektu -lOpenGL32 -lfreeGLUT)
````
oraz zainstalować FreeGLUT, przekopiuj po prostu pliki do C:/MinGW
````
https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MinGW.zip
````
Przed kompilacją zmienić kodowanie pliku na IBM852!

# 1 termin oddania pracy - gotowe

- Ujednolicenie nazewnictwa wewnątrz programu
- Testy w celu wykrycia ewentualnych błędów
- utworzenie komentarzy do ważniejszych części kodu
- utworzenie dokumentacji w programie Doxygen

# 2 Kamień milowy - gotowe

- Przedstawienie kroków pracy algorytmu.
- Pomiar czasu pracy algorytmu.
- Zapis wyników do pliku
- Przedstawienie ilości wykonywanych operacji

# 1 Kamień milowy - gotowe
- Możliwość podania ilości i współrzędnych punktów.
- Opcja losowania współrzędnych z danego zakresu.
- Zastosowanie algorytmu.
- Odczyt punktów z pliku.
