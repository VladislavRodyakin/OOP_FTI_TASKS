#pragma once
#include <vector>
#include <queue>

class ImageFIFO final {
	const size_t m_block_size; // how do we use it?
	const size_t m_max_queue_size;
	std::vector<unsigned int*> data_container;
	std::vector<bool> ready_for_writing_state;
	std::queue<void*> ready_for_read_blocks;
public:
	ImageFIFO(size_t blockSize, size_t maxBlocks) : m_block_size{ blockSize }, m_max_queue_size{ maxBlocks } {
		data_container = std::vector<unsigned int*>(maxBlocks, nullptr);
		ready_for_writing_state = std::vector<bool>(maxBlocks, true);
	}
	~ImageFIFO() {
		data_container.clear(); // from what i seen in source code, it should call delete for all pointers inside. if not, redo everything (probably using shared_ptr)
		while (ready_for_writing_state.empty() != true) {
			delete ready_for_read_blocks.front();
			ready_for_read_blocks.pop();
		}
	}

	// метод, вызываемый потоком-писателем, для получения указателя на очередной свободный блок данных
	void* getFree();

	// метод, вызываемый потоком-писателем, помечающий, что найденный ранее блок данных заполнен и готов к передаче
	void addReady(void* data);

	// метод, вызываемый потоком-читателем, для получения указателя на очередной готовый блок данных
	void* getReady();

	// метод, вызываемый потоком-читателем, помечающий, что выданный ранее блок данных обработан, освобождён и может повторно использоваться очередью
	void addFree(void* data);
};
