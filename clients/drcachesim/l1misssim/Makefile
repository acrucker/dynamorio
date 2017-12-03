all:
	g++ l1missdriver.cpp ../simulator/cache.cpp \
			../simulator/caching_device.cpp \
			../simulator/caching_device_stats.cpp \
			../simulator/cache_stats.cpp \
			../simulator/cache_lru.cpp \
			../simulator/cache_fifo.cpp \
			-std=gnu++14 -I.. -I../common -I../simulator -lbz2 \
			-lboost_iostreams -o l1missdriver -D_EXTERNAL_ -g
