# Klasa 'paczkomat' (ocena max. 5,0)

Program symuluje działanie paczkomatu składającego się ze skrzynek o trzech wielkościach: mała, średnia i duża.

1. Zdefiniuj klasę `skrzynka`, której składnikami prywatnymi będą np. `wysokosc` i `szerokosc`, zadawane w konstruktorze klasy na podstawie wartości przesłanych argumentów oraz zmienna określająca stan skrzynki o nazwie np. `czy_pelna`, `czy_pusta`, `zajeta`, `wolna` - zależnie od pomysłu i przyjętej logiki.

2. Zdefiniuj funkcję składową klasy `skrzynka` np. "**bool** skrzynka::wloz_paczke(**float** wys, **float** szer)", której zadaniem będzie:
   - sprawdzenie i poinformowanie na ekranie, jeśli skrzynka jest już zajęta oraz zwrócenie wartości **false**,
   - przyjęcie paczki gdy skrzynka jest pusta, a paczka się zmieści (przez porównanie obu par wymiarów), zmiana stanu na zajęty oraz zwrócenie wartości **true**,
   - poinformowanie jeśli skrzynka jest pusta, ale paczka się nie mieści oraz zwrócenie wartości **false**
3. Zdefiniuj klasę `paczkomat`, w skład którego będzie wchodzić tablica wskaźników do obiektów klasy `skrzynka` o ustalonym rozmiarze, np. 12.

4. Montowania skrzynek w paczkomacie możesz dokonać przy użyciu odpowiedniej funkcji lub bezpośrednio w konstruktorze klasy `paczkomat`. Wymiary i liczbę skrzynek danej wielkości dobierz samodzielnie.

5. Zdefiniuj funkcję składową klasy `paczkomat` np. "**void** paczkomat::wloz_paczke(**int** ID_skrzynki, **float** wys, **float** szer)", której zadaniem jest próba włożenia paczki do skrzynki o zadanym numerze i wyświetlenie komunikatu, czy operacja się udała (na podstawie wartości zwracanej przez funkcję składową danej skrzynki).

6. W funkcji głównej, zdefiniuj obiekt klasy `paczkomat`. Interfejs użytkownika nie jest wymagany. Zasymuluj wkładanie co najmniej trzech paczek o wymiarach pasujących do różnych skrzynek tak, aby dwukrotnie operacja się nie udała (za mała lub zajęta skrzynka), ale ostatecznie wszystkie paczki znalazły się w paczkomacie.

7. Podziel odpowiednio projekt na plik nagłówkowy, plik definicji oraz plik funkcji głównej i prześlij je na platformę do oceny.

---

## Dla ambitnych:

Zmodyfikuj i rozbuduj klasy `skrzynka` i `paczkomat` według własnego pomysłu. Możesz dopisać np.:
- funkcję do wyjmowania paczki ze skrzynki,
- losowanie 6-cyfrowego kodu otwierającego skrzynkę po umieszczeniu paczki przyporządkowanego do danej skrzynki,
- utworzyć interfejs użytkownika.
