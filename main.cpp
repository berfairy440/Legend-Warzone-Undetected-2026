#include <iostream>
#include <thread>
#include "dma_handler.hpp"
#include "offsets.h"

int main() {
    std::cout << "[SENTINEL] Searching for hardware... " << std::flush;

    if (!DMA::Initialize()) {
        std::cout << "FAILED" << std::endl;
        return -1;
    }
    std::cout << "SUCCESS" << std::endl;

    while (DMA::IsActive()) {
        uint64_t client_info = DMA::Read<uint64_t>(Offsets::Base + Offsets::ClientInfo);
        
        // Parallelized thread loop for feature execution
        DMA::UpdateEntities(client_info);
        DMA::UpdateAimbot();
        
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }

    return 0;
}
