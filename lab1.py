import doctest

class Book:
    def __init__(self, title: str, author: str, page_count: int):
        """
        Создание и подготовка к работе объекта "книга"
        :param title: название книги
        :param author: имя автора
        :param page_count: число страниц
        Примеры:
        >>> book = Book("Death Troopers", "Joe Schreiber", 278)  # инициализация экземпляра класса
        """
        if not isinstance(page_count, int):
            raise TypeError("число страниц должно быть типа int")
        if page_count < 0:
            raise ValueError("число страниц должно быть положительным числом")
        self.height = page_count

        self.title = title
        self.author = author

    def open(self) -> None:
        """
        открыть книгу
        Примеры:
        >>> book = Book("Death Troopers", "Joe Schreiber", 278)
        >>> book.open()
        """

    def next(self) -> None:
        """
        перелистнуть страницу
        Примеры:
        >>> book = Book("Death Troopers", "Joe Schreiber", 278)
        >>> book.next()
        """

    def back(self) -> None:
        """
        Предыдущая страница
        Примеры:
        >>> book = Book("Death Troopers", "Joe Schreiber", 278)
        >>> book.back()
        """


class Vegetable:
    def __init__(self, name: str, color: str):
        """
                Создание и подготовка к работе объекта "овощ"
                :param name: название овощ
                :param color: цвет овощ
                Примеры:
                >>> pepper = Vegetable("pepper", "red")  # инициализация экземпляра класса
                """
        self.name = name
        self.color = color

    def slice(self) -> None:
        """
        нарезать овощ
        :return: ваши овощ нарезан
        Примеры:
        >>> pepper = Fruit("pepper", "red")
        >>> pepper.slice()
        """

    def eat(self) -> None:
        """
        съесть овощ
        :return: овощ съели
        Примеры:
        >>> pepper = Fruit("pepper", "red")
        >>> pepper.eat()
        """
class Tree:
    def __init__(self, height: int, age: int, type_tree: str):
        """
        Создание и подготовка к работе объекта "дом"
        :param height: высота дерева
        :param age: возраст дерева
        :param type_tree: вид дерева
        Примеры:
        >>> tree = Tree(500, 20, "dub")  # инициализация экземпляра класса
        """
        if not isinstance(height, int):
            raise TypeError("высота должна быть типа int")
        if height < 0:
            raise ValueError("высота должна быть положительным числом")
        self.height = height

        if not isinstance(age, int):
            raise TypeError("возраст должен быть типа int")
        if age < 0:
            raise ValueError("возраст должен быть положительным числом")
        self.age = age

        self.type_tree = type_tree

    def shed_leaves(self) -> bool:
        """
        Функция которая проверяет дерево сбрасывает листья
        :return: дерево сбрасывает листья
        Примеры:
        >>> tree = Tree(500, 20, "dub")
        >>> tree.shed_leaves()
        """

    def get_type(self) -> str:
        """
        Вернет тип дерева
        :return: тип дерева
        Примеры:
        >>> tree = Tree(500, 20, "dub")
        >>> tree.get_type()
        """

if __name__ == "__main__":
    doctest.testmod()