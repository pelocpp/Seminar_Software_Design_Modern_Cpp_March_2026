// =====================================================================================
// TypeErasure.cpp
// =====================================================================================

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <variant>
#include <print>

// =====================================================================================

namespace BookStoreUsingDynamicPolymorphism {

    struct IMedia
    {
        virtual ~IMedia() {};

        virtual double getPrice() const = 0;
        virtual std::size_t getCount() const = 0;
    };

    class Book : public IMedia
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        std::size_t      m_count;

    public:
        // c'tor
        Book(const std::string& author, const std::string& title, double price, std::size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count }
        {
        }

        // getter / setter
        const std::string& getAuthor() const { return m_author; }
        const std::string& getTitle() const { return m_title; }

        // interface 'IMedia'
        double getPrice() const override { return m_price; }
        std::size_t getCount() const override { return m_count; }
    };

    class Movie : public IMedia
    {
    private:
        std::string m_title;
        std::string m_director;
        double      m_price;
        std::size_t      m_count;

    public:
        // c'tor
        Movie(const std::string& title, const std::string& director, double price, std::size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count }
        {
        }

        // getter / setter
        const std::string& getTitle() const { return m_title; }
        const std::string& getDirector() const { return m_director; }

        // interface 'IMedia'
        double getPrice() const override { return m_price; }
        std::size_t getCount() const override { return m_count; }
    };

    class Bookstore
    {
    private:
        // IMedia*
        using Stock = std::vector<std::shared_ptr<IMedia>>;
        using StockList = std::initializer_list<std::shared_ptr<IMedia>>;

        Stock m_stock;

    public:
        // c'tor
        explicit Bookstore(StockList stock) : m_stock{ stock } {}

        // public interface
        double totalBalance() const {

            double total{};

            for (const auto& media : m_stock) {
                total += media->getPrice() * media->getCount();
            }

            return total;
        }

        std::size_t count() const {

            std::size_t total{};

            for (const auto& media : m_stock) {
                total += media->getCount();
            }

            return total;
        }

        void addMedia(const std::shared_ptr<IMedia>& media) {
            m_stock.push_back(media);
        }
    };

    static void test_bookstore_polymorphic_01() {

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };
        std::shared_ptr<IMedia> javaBook{ std::make_shared<Book>("Java", "James Gosling", 17.99, 21) };
        std::shared_ptr<IMedia> cppBook{ std::make_shared<Book>("C++", "Bjarne Stroustrup", 16.99, 4) };
        std::shared_ptr<IMedia> csharpBook{ std::make_shared<Book>("C#", "Anders Hejlsberg", 21.99, 8) };

        std::shared_ptr<IMedia> movieTarantino{ std::make_shared<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3) };
        std::shared_ptr<IMedia> movieBond{ std::make_shared<Movie>("Spectre", "Sam Mendes", 8.99, 6) };

        Bookstore bookstore{
            cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_polymorphic_02() {

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };
        std::shared_ptr<IMedia> movieBond{ std::make_shared<Movie>("Spectre", "Sam Mendes", 8.99, 6) };

        Bookstore bookstore{ cBook, movieBond };

        std::shared_ptr<IMedia> csharpBook{ std::make_shared<Book>("C#", "Anders Hejlsberg", 21.99, 8) };
        bookstore.addMedia(csharpBook);

        std::shared_ptr<IMedia> movieTarantino{ std::make_shared<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3) };
        bookstore.addMedia(movieTarantino);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }
}

// =====================================================================================

namespace BookStoreUsingTypeErasure {

    class Book
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        std::size_t      m_count;

    public:
        // c'tor
        Book(const std::string& author, const std::string& title, double price, std::size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count }
        {
        }

        // getter / setter
        const std::string& getAuthor() const { return m_author; }
        const std::string& getTitle() const { return m_title; }

        // Hmmm, kann man das fixieren ... so wie IMedia ????
        double getPrice() const { return m_price; }
        std::size_t getCount() const { return m_count; }
    };

    class Movie
    {
    private:
        std::string m_title;
        std::string m_director;
        double      m_price;
        std::size_t      m_count;

    public:
        // c'tor
        Movie(const std::string& title, const std::string& director, double price, std::size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count }
        {
        }

        // getter / setter
        const std::string& getTitle() const { return m_title; }
        const std::string& getDirector() const { return m_director; }

        // Wie oben
        double getPrice() const { return m_price; }
        std::size_t getCount() const { return m_count; }
    };

    template<typename T>
    concept MediaConcept = requires (const T& m)
    {
        { m.getPrice() } -> std::same_as<double>;
        { m.getCount() } -> std::same_as<std::size_t>;
    };

    template <typename ... TMedia>
    
        // Für eine variadische Anzahl verwenden wir FOLDING
        requires (MediaConcept<TMedia> && ...)
    
    class Bookstore
    {
    private:
        using StockType = std::variant<TMedia ...>;
        using Stock = std::vector<StockType>;
        using StockList = std::initializer_list<StockType>;

        Stock m_stock;

    public:
        explicit Bookstore(StockList stock) : m_stock{ stock } {}

        // template member method
        template <typename T>
            requires MediaConcept<T>
        void addMedia(const T& media) {
            m_stock.push_back(std::variant<TMedia ...>{ media });  // detailed notation
            m_stock.push_back(media);                  // implicit type conversion (T => std::variant<T>)
        }

        // or
        void addMediaEx(const MediaConcept auto& media) {
            m_stock.push_back(media);
        }

        // public interface
        double totalBalance() const {

            double total{};

            for (const auto& media : m_stock) {  // media:  std::variant

                double price{};
                std::size_t count{};

                std::visit(
                    [&](const auto& element) {       // generic lambda 
                        price = element.getPrice();  // element: Book,Movie
                        count = element.getCount();  // ist "immer" schneller
                    },
                    media
                );

                total += price * count;
            }

            return total;
        }

        std::size_t count() const {

            std::size_t total{};

            for (const auto& media : m_stock) {

                std::size_t count{};

                std::visit(
                    [&](const auto& element) {
                        count = element.getCount();
                    },
                    media
                );

                total += count;
            }

            return total;
        }

        // -----------------------------------------------
        // demonstrating std::visit with returning a value

        double totalBalanceEx() const {

            double total{};

            for (const auto& media : m_stock) {

                total += std::visit(
                    [](const auto& element) {
                        double price = element.getPrice();
                        std::size_t count = element.getCount();
                        return price * count;
                    },
                    media
                );
            }

            return total;
        }

        std::size_t countEx() const {

            std::size_t total{};

            for (const auto& element : m_stock) {

                total += std::visit(
                    [](const auto& element) {
                        return element.getCount();
                    },
                    element
                );
            }

            return total;
        }
    };

    static void test_bookstore_type_erasure_01() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Book javaBook{ "Java", "James Gosling", 17.99, 21 };
        Book cppBook{ "C++", "Bjarne Stroustrup", 16.99, 4 };
        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };

        Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore < Book, Movie > ;

        MyBookstore bookstore{
            cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);
        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_type_erasure_02() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore{ cBook, movieBond };

        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };
        bookstore.addMedia(csharpBook);

        Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
        bookstore.addMediaEx(movieTarantino);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    class BluRay
    {
    public:
        BluRay() = default;

        // getter / setter
        std::size_t getCount() const { return 0; }
        double getPrice() const { return 0.0; }   // put into comments
    };

    static void test_bookstore_type_erasure_05() {

        // verifying concept 'MediaConcept'
        Bookstore<Book, BluRay, Movie> bookstore{};
    }
}

// =====================================================================================

void main_static_polymorphismus()
{
    using namespace BookStoreUsingDynamicPolymorphism;
    using namespace BookStoreUsingTypeErasure;

    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_01();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_02();


    BookStoreUsingTypeErasure::test_bookstore_type_erasure_01();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
