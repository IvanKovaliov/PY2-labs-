import doctest


class Vehicle:
    """Базовый класс для транспортных средств"""

    def __init__(self, brand: str, model: str, year: int):
        """
        Конструктор класса Vehicle.
        :param brand: Марка транспортного средства.
        :param model: Модель транспортного средства.
        :param year: Год выпуска транспортного средства.
        Примеры:
        >>> vehicle = Vehicle("Achleitner Carrier", "4", 2011)
        """
        self.brand = brand
        self.model = model
        self.year = year

    def __str__(self) -> str:
        return f"{self.brand} {self.model} ({self.year})"

    def __repr__(self) -> str:
        return f"Vehicle(brand='{self.brand}', model='{self.model}', year={self.year})"

    def start(self) -> None:
        """Запускает двигатель транспортного средства.
        Примеры:
        >>> vehicle = Vehicle("Achleitner", "4", 2011)
        >>> vehicle.start()
        """

    def stop(self) -> None:
        """Останавливает двигатель транспортного средства.
        Примеры:
        >>> vehicle = Vehicle("Achleitner", "4", 2011)
        >>> vehicle.stop()
        """


class Car(Vehicle):
    """Дочерний класс для автомобиля"""

    def __init__(self, brand: str, model: str, year: int, color: str):
        """
        Конструктор класса Car.
        :param brand: Марка автомобиля.
        :param model: Модель автомобиля.
        :param year: Год выпуска автомобиля.
        :param color: Цвет автомобиля.
        Примеры:
        >>> Achleitner = Car("Achleitner", "model Carrier", 2016, "green")
        """
        super().__init__(brand, model, year)
        self.color = color

    def __str__(self) -> str:
        return f"{self.color} {self.brand} {self.model} ({self.year})"

    def __repr__(self) -> str:
        return f"Car(brand='{self.brand}', model='{self.model}', year={self.year}, color='{self.color}')"

    def lock_doors(self) -> None:
        """Закрывает двери автомобиля.
        Примеры:
        >>> Achleitner = Car("tesla", "model Carrier", 2016, "green")
        >>> Achleitner.lock_doors()
        """
        self.doors_locked = True

    def unlock_doors(self) -> None:
        """Открывает двери автомобиля.
        Примеры:
        >>> Achleitner = Car("Achleitner", "model Carrier", 2016, "green")
        >>> Achleitner.unlock_doors()
        """
        self.doors_locked = False

    def stop(self) -> None:
        """Останавливает двигатель автомобиля.
        Метод перегружен, так как необходимо выключить музыку
        Примеры:
        >>> Achleitner = Car("Achleitner", "model Carrier", 2016, "green")
        >>> Achleitner.stop()
        """
        self.engine_running = False
        self.turn_off_music()

    def play_music(self, song: str) -> None:
        """
        Воспроизводит музыку в автомобиле.
        :param song: Название песни.
        Примеры:
        >>> Achleitner = Car("Achleitner", "model Carrier", 2016, "green")
        >>> Achleitner.play_music("We Are Number One")
        """
        self.current_song = song

    def turn_off_music(self) -> None:
        """
        Выключить музыку в автомобиле.
        Примеры:
        >>> Achleitner = Car("Achleitner", "model Achleitner", 2016, "green")
        >>> Achleitner.turn_off_music()
        """
        self.current_song = None


if __name__ == "__main__":
    doctest.testmod()