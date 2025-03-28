Dağıtık Sistemler Ödevi - MPI ve OpenMP ile Paralel Matris Çarpımı

Bu proje, Docker kullanarak çok düğümlü bir dağıtık sistem oluşturur ve MPI ile OpenMP'yi birlikte kullanarak paralel matris çarpımı gerçekleştirir.

Gereksinimler

Docker

Docker Compose

Proje Yapısı

Dockerfile: MPI ve OpenMP ortamını içeren Docker imajı

docker-compose.yml: Birden fazla düğümü yapılandıran Docker Compose dosyası

matrix_multiplication.c: MPI ve OpenMP kullanan matris çarpımı programı

data/: Veri dosyaları için dizin

Kurulum ve Çalıştırma

Projeyi klonlayın:

git clone <repo-url>
cd <proje-dizini>

Docker imajını oluşturun ve konteynerleri başlatın:

docker-compose up --build

Nasıl Çalışır?

Sistem 3 düğümden oluşur (worker1, worker2, worker3).

Her düğüm, MPI kullanarak belirli matris satırlarını işler.

OpenMP ile her düğümde matris satırlarının çarpımı paralel gerçekleştirilir.

Sonuçlar ana düğümde (worker1) toplanarak nihai matris elde edilir.

Özelleştirme

MATRIX_SIZE: İşlenecek matrisin boyutu (N x N)

OMP_NUM_THREADS: Her düğümde çalışacak OpenMP thread sayısı

Düğüm sayısı: docker-compose.yml dosyasında değiştirilebilir
