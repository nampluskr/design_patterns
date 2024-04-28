from abc import ABC, abstractmethod

## Abstract Localizer
class AbstractLocalizer(ABC):
    @abstractmethod
    def localize(self, msg):
        pass

class FrenchLocalizer(AbstractLocalizer):
    def __init__(self):
        self.translations = {
            "car": "voiture",
            "bike": "bicyclette",
            "cycle":"cyclette",
        }

    def localize(self, msg):
        return self.translations[msg]


class SpanishLocalizer(AbstractLocalizer):
    def __init__(self):
        self.translations = {
            "car": "voiture",
            "bike": "bicyclette",
            "cycle":"cyclette",
        }

    def localize(self, msg):
        return self.translations[msg]


class EnglishLocalizer(AbstractLocalizer):
    def localize(self, msg):
        return msg


## Factory Interface
class LocalizerFactory(ABC):
    @abstractmethod
    def create_localizer(self) -> AbstractLocalizer:
        pass

class FrenchLocalizerFactory(LocalizerFactory):
    def create_localizer(self) -> AbstractLocalizer:
        return FrenchLocalizer()

class SpanishLocalizerFactory(LocalizerFactory):
    def create_localizer(self) -> AbstractLocalizer:
        return SpanishLocalizer()

class EnglishLocalizerFactory(LocalizerFactory):
    def create_localizer(self) -> AbstractLocalizer:
        return EnglishLocalizer()


## Factory class
class Factory:
    def __init__(self):
        self.factories = {
            "French": FrenchLocalizerFactory(),
            "Spanish": SpanishLocalizerFactory(),
            "English": EnglishLocalizerFactory(),
        }
    def create_localizer(self, language="English") -> AbstractLocalizer:
        return self.factories[language].create_localizer()


if __name__ == "__main__":

    message = ["car", "bike", "cycle"]

    factory = Factory()
    french_localizer = factory.create_localizer("French")
    english_localizer = factory.create_localizer("English")
    spahish_localizer = factory.create_localizer("Spanish")

    for msg in message:
        print(french_localizer.localize(msg))
        print(english_localizer.localize(msg))
        print(spahish_localizer.localize(msg))