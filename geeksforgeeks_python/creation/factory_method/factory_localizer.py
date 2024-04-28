"""
- 클라이언트 코드에서 구체 클래스의 특정 구현 세부 정보를 추상화
"""
from abc import ABC, abstractmethod


class FrenchLocalizer:
    def __init__(self):
        self.translations = {
            "car": "voiture",
            "bike": "bicyclette",
            "cycle":"cyclette",
        }

    def localize(self, msg):
        return self.translations[msg]


class SpanishLocalizer:
    def __init__(self):
        self.translations = {
            "car": "voiture",
            "bike": "bicyclette",
            "cycle":"cyclette",
        }

    def localize(self, msg):
        return self.translations[msg]


class EnglishLocalizer:
    def localize(self, msg):
        return msg

## factory function
def create_localizer(language="English"):
    localizers = {
        "French": FrenchLocalizer,
        "English": EnglishLocalizer,
        "Spanish": SpanishLocalizer,
    }
    return localizers[language]()


## factory class
class LocalizerFactory:
    def __init__(self):
        self.localizers = {
            "English": EnglishLocalizer(),
            "Spanish": SpanishLocalizer(),
            "French": FrenchLocalizer(),
        }
    def create_localizer(self, language="English"):
        return self.localizers[language]


if __name__ == "__main__":

    message = ["car", "bike", "cycle"]

    if 0:   ## Without factory method
        f = FrenchLocalizer()
        e = EnglishLocalizer()
        s = SpanishLocalizer()

        for msg in message:
            print(f.localize(msg))
            print(e.localize(msg))
            print(s.localize(msg))

    if 0:   ## With factory function
        f = create_localizer("French")
        e = create_localizer("English")
        s = create_localizer("Spanish")

        for msg in message:
            print(f.localize(msg))
            print(e.localize(msg))
            print(s.localize(msg))

    if 1:  ## With factory class
        factory = LocalizerFactory()
        f = factory.create_localizer("French")
        e = factory.create_localizer("English")
        s = factory.create_localizer("Spanish")

        for msg in message:
            print(f.localize(msg))
            print(e.localize(msg))
            print(s.localize(msg))

