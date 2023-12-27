#pragma once
#include <vector>
#include <queue>
#include <mutex>

class ImageFIFO final {
	const size_t m_block_size; // how do we use it? probably underlying list like unsigned int bmp[m_block_size]
	const size_t m_max_queue_size;
	std::vector<unsigned int*> data_container;
	std::vector<bool> ready_for_writing_state;
	std::queue<void*> ready_for_read_blocks;
	std::mutex mut;
	/*
	std::mutex getFree_mutex;
	std::mutex addReady_mutex;
	std::mutex getReady_mutex;
	std::mutex addFree_mutex;*/
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
	void* getFree() {
		//const std::lock_guard<std::mutex> lock(getFree_mutex);
		const std::lock_guard<std::mutex> lock(mut);
		while (true) {
			for (int i = 0; i < m_max_queue_size; i++) {
				if (ready_for_writing_state[i] == true && data_container[i] == nullptr) {
					ready_for_writing_state[i] = false;
					return data_container[i];
				}
			}
		}
	}

	// метод, вызываемый потоком-писателем, помечающий, что найденный ранее блок данных заполнен и готов к передаче
	void addReady(void* data) {
		//const std::lock_guard<std::mutex> lock(addReady_mutex);
		const std::lock_guard<std::mutex> lock(mut);
		for (int i = 0; i < m_max_queue_size; i++) {
			if (data_container[i] == data) {
				ready_for_read_blocks.push(data);
				break;
			}
		}
	}

	// метод, вызываемый потоком-читателем, для получения указателя на очередной готовый блок данных
	void* getReady() {
		//const std::lock_guard<std::mutex> lock(getReady_mutex);
		const std::lock_guard<std::mutex> lock(mut);
		while (true) {
			unsigned int* tmp = (unsigned int*)ready_for_read_blocks.front();
			if (tmp != nullptr) {
				ready_for_read_blocks.pop();
				return tmp;
			}
		}
	}

	// метод, вызываемый потоком-читателем, помечающий, что выданный ранее блок данных обработан, освобождён и может повторно использоваться очередью
	void addFree(void* data) {
		//const std::lock_guard<std::mutex> lock(addFree_mutex);
		const std::lock_guard<std::mutex> lock(mut);
		for (int i = 0; i < m_max_queue_size; i++) {
			if (data_container[i] == data) {
				ready_for_writing_state[i] = true;
				break;
			}
		}
	}
};
