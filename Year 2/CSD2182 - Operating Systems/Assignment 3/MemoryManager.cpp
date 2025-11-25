#include "MemoryManager.h"

// Constructor for the MemCtrlBlk structure
MemoryManager::MemCtrlBlk::MemCtrlBlk(void* ptr, int size)
{
    this->data = ptr;
    this->size = size;
    this->allocated = false;
}

// Constructor for MemoryManager
MemoryManager::MemoryManager(int total_bytes)
{
    // Allocate the memory pool
    mempool = malloc(total_bytes);
    
    // Create initial memory control block for the entire pool
    MemCtrlBlk initial_block(mempool, total_bytes);
    
    // Initialize the memory block list with the initial block
    memoryBlock.push_back(initial_block);
}

// Destructor for MemoryManager
MemoryManager::~MemoryManager()
{
    free(mempool);
}

// Allocate memory from the pool
void* MemoryManager::allocate(int bytes)
{
    // Find first unallocated block that's big enough
    for (auto it = memoryBlock.begin(); it != memoryBlock.end(); ++it)
    {
        if (!it->allocated && it->size >= bytes)
        {
            // If block is larger than needed, split it
            if (it->size > bytes)
            {
                void* splitAddr = static_cast<char*>(it->data) + bytes;
                int remainingSize = it->size - bytes;

                // Create new block for the remaining space
                MemCtrlBlk newBlock(splitAddr, remainingSize);
                
                // Update current block size
                it->size = bytes;
                
                // Insert new block after current one
                memoryBlock.insert(std::next(it), newBlock);
            }
            
            // Initialize allocated memory to zero
            char* memPtr = static_cast<char*>(it->data);
            for (int i = 0; i < bytes; i++) {
                memPtr[i] = 0;
            }
            
            // Mark block as allocated
            it->allocated = true;
            
            return it->data;
        } 
    }
    // No suitable block found
    return nullptr;
}

// Deallocate memory and attempt to merge adjacent free blocks
void MemoryManager::deallocate(void *pointer)
{
    // Find the block containing this pointer
    for (auto it = memoryBlock.begin(); it != memoryBlock.end(); ++it)
    {
        if (it->data == pointer)
        {
            // Mark block as unallocated
            it->allocated = false;

            // Try to merge with previous blocks
            auto prev = it;
            while (it != memoryBlock.begin())
            {
                --prev;
                if (prev->allocated)
                {
                    break;
                }
                // Merge blocks by adding sizes
                prev->size += it->size;
                // Remove the merged block
                it = memoryBlock.erase(it);
                it = prev;
            }
            
            // Try to merge with subsequent blocks
            auto next = it;
            ++next;
            while (next != memoryBlock.end() && !next->allocated)
            {
                // Merge blocks by adding sizes
                it->size += next->size;
                // Remove the merged block
                next = memoryBlock.erase(next);
            }
            return;
        }
    }
}

void MemoryManager::dump(std::ostream& out)
{
    // Iterate through all memory blocks
    for (const auto& block : memoryBlock)
    {
        // Calculate and output the offset from start of mempool
        out << "relative to start address: ";
        out << std::hex << (static_cast<char*>(block.data) - static_cast<char*>(mempool)) << std::endl;

        // Output the size of the block
        out << "  byte count: ";
        out << std::hex << block.size << std::endl;

        // Output the allocation state
        out << "  allocated? ";
        out << std::boolalpha << block.allocated << std::endl;
    }
}