// #include <stdio.h>
// #include <stdint.h>
// #include <string.h>
//
// struct direct_mapped_Cache{
// 	uint64_t lines[512]; //this stores cache line tags and entries
// 	int cache_hits;
// 	int cache_misses;
// };
//
// struct fully_assoc_Cache{
// 	uint64_t visits[512]; //this stores the frequency of visits to each line
// 	uint64_t lines[512]; //this stores cache line tags
// 	int cache_hits;
// 	int cache_misses;
// };
//
// struct eightway_set_assoc_Cache{
// 	uint64_t sets[64][8]; //establishes a cache with 64 sets of 8 lines
// 	uint64_t visits[64][8];//stores the frequency of visits to each line
// 	int cache_hits;
// 	int cache_misses;
// };

uint64_t memoryToBinary(char memory[]);
void simulateAssoc(struct fully_assoc_Cache *cache, uint64_t memoryAccessed);
void simulateDirect(struct direct_mapped_Cache *cache, uint64_t memoryAccessed);
void simulate8way(struct eightway_set_assoc_Cache *cache, uint64_t memoryAccessed);
void updateCache(struct fully_assoc_Cache *cache, uint64_t leading_bits);
void updateCache2(struct eightway_set_assoc_Cache *cache, uint64_t set, uint64_t tag);

int main(int argc, char *argv[]) /* Takes in Command Line Arguments Type of Cache and Filename*/
{	//lines 38 through 65 are all for set up//
	char* filename = argv[2];
	char fully[20];
	char eight[30];
	char direct[20];
	strcpy(fully, "fully_assoc_Cache");
	strcpy(eight, "eightway_set_assoc_Cache");
	strcpy(direct, "direct_mapped_Cache");
	struct fully_assoc_Cache cache_one;
	struct eightway_set_assoc_Cache cache_two;
	struct direct_mapped_Cache cache_three;
	cache_one.cache_hits = 0;
	cache_one.cache_misses = 0;
	cache_two.cache_hits = 0;
	cache_two.cache_misses = 0;
	cache_three.cache_hits = 0;
	cache_three.cache_misses = 0;

	for(int i =0; i<512; i++){
		cache_one.visits[i] = 0;
		cache_one.lines[i] = 0;
		cache_three.lines[i] = 0;
	}
	for(int x =0; x<64; x++){
		for(int y = 0; y<8; y++){
			cache_two.sets[x][y] = 0;
			cache_two.visits[x][y] = 0;
		}
	}

	char file[20];
   	FILE *fp;

   	/* opening file for reading */
   	fp = fopen(filename , "r");

	while(fgets(file, 20, fp)!= NULL){
		uint64_t address = memoryToBinary(file);

		if(strncmp(argv[1], fully, 17)==0){
			simulateAssoc(&cache_one, address);
		}
		if(strncmp(argv[1], eight, 24)==0){
			simulate8way(&cache_two, address);
		}
		if(strncmp(argv[1], direct, 19)==0){
			simulateDirect(&cache_three, address);
		}
	}

	fclose(fp);

	if(strncmp(argv[1], fully,17)==0){
		printf("Cache Hits: %d\n", cache_one.cache_hits);
		printf("Cache Misses: %d\n", cache_one.cache_misses);
		printf("Percent Cache Hits: %.2f\n", (double)cache_one.cache_hits/(cache_one.cache_hits+cache_one.cache_misses));
		printf("Percent Cache Misses: %.2f\n", (double)cache_one.cache_misses/(cache_one.cache_hits+cache_one.cache_misses));
	}
	if(strncmp(argv[1], eight, 24)==0){
		printf("Cache Hits: %d\n", cache_two.cache_hits);
		printf("Cache Misses: %d\n", cache_two.cache_misses);
		printf("Percent Cache Hits: %.2f\n", (double)cache_two.cache_hits/(cache_two.cache_hits+cache_two.cache_misses));
		printf("Percent Cache Misses: %.2f\n", (double)cache_two.cache_misses/(cache_two.cache_hits+cache_two.cache_misses));
	}
	if(strncmp(argv[1], direct, 19)==0){
		printf("Cache Hits: %d\n", cache_three.cache_hits);
		printf("Cache Misses: %d\n", cache_three.cache_misses);
		printf("Percent Cache Hits: %.2f\n", (double)cache_three.cache_hits/(cache_three.cache_hits+cache_three.cache_misses));
		printf("Percent Cache Misses: %.2f\n", (double)cache_three.cache_misses/(cache_three.cache_hits+cache_three.cache_misses));
	}
}
//
// uint64_t memoryToBinary(char memory[])
// /* For each line, memoryToBits converts the value to "binary" (a uint64 that can have bitwise operations done on it) */
// {
// 	uint64_t binary = 0;
// 	int i = 0;
// 	while(memory[i]!= '\n'){
//    		if (memory[i]<= '9' && memory[i]>='0'){
//    			binary = (binary*16) + (memory[i] - '0');
//    		}else{
//    			if(memory[i] == 'a'){
//    		 		binary = (binary*16) + 10;
//    		 	}
//    		 	if(memory[i] == 'b'){
//    		 		binary = (binary*16) + 11;
//    		 	}
//    		 	if(memory[i] == 'c'){
//    		 		binary = (binary*16) + 12;
//    		 	}
//    		 	if(memory[i] == 'd'){
//    		 		binary = (binary*16) + 13;
//    		 	}
//    		 	if(memory[i] == 'e'){
//    		 		binary = (binary*16) + 14;
//    		 	}
//    		 	if(memory[i] == 'f'){
//    		 		binary = (binary*16) + 15;
//    		 	}
//    		}
//    	    i++;
//    	}
//
//     return binary;
// }

// void simulateAssoc(struct fully_assoc_Cache *cache, uint64_t memoryAccessed)
// {
// 	uint64_t leading_twenty_six_bits = memoryAccessed >> 6;
//
// 	for (int i = 0; i<512; i++){
// 		if (cache->lines[i] == leading_twenty_six_bits){
// 			cache->visits[i] += 1;
// 			cache->cache_hits += 1;
// 			return;
// 		}
// 	}
// 	cache->cache_misses +=1;
// 	updateCache(cache, leading_twenty_six_bits);
// }

// void simulateDirect(struct direct_mapped_Cache *cache, uint64_t memoryAccessed)
// {
// 	uint64_t mask = 0xff;
// 	uint64_t cache_row = (memoryAccessed >> 6) & mask;
// 	uint64_t tag = memoryAccessed >> 15;
//
// 	if (cache->lines[cache_row] == tag){
// 		cache->cache_hits +=1;
// 	}else{ni
// 		cache->cache_misses += 1;
// 		cache->lines[cache_row] = tag;
// 	}
// }
//
// void simulate8way(struct eightway_set_assoc_Cache *cache, uint64_t memoryAccessed)
// {
// 	uint64_t mask = 0x3f;
// 	uint64_t cache_set = (memoryAccessed >> 6) & mask;
// 	uint64_t tag = memoryAccessed >> 12;
//
// 	for(int i = 0; i <8; i++){
// 		if(cache->sets[cache_set][i] == tag){
// 			cache->cache_hits += 1;
// 			cache->visits[cache_set][i] += 1;
// 			return;
// 		}
// 	}
//
// 	cache->cache_misses += 1;
// 	updateCache2(cache, cache_set, tag);
//
// }
//
// void updateCache(struct fully_assoc_Cache *cache, uint64_t leading_bits)
// {
// 	int lrv = cache->visits[0]; //least recently visisited
// 	for(int x = 0; x<512; x++){
// 		if(cache->visits[x] < lrv){
// 			lrv = cache->visits[x];
// 		}
// 	}
//
// 	for(int i= 0; i < 512; i++){
// 		if(cache->visits[i] == lrv){
// 			cache->lines[i] = leading_bits;
// 			cache->visits[i] = 0;
// 			return;
// 		}
// 	}
// }
//
// void updateCache2(struct eightway_set_assoc_Cache *cache, uint64_t set, uint64_t tag)
// {
// 	int lrv = cache->visits[set][0]; //least recently visisited
// 	for(int x = 0; x<8; x++){
// 		if(cache->visits[set][x] < lrv){
// 			lrv = cache->visits[set][x];
// 		}
// 	}
//
// 	for(int x = 0; x<8; x++){
// 		if(cache->visits[set][x] == lrv){
// 			cache->sets[set][x] = tag;
// 			cache->visits[set][x] = 0;
// 			return;
// 		}
// 	}
// }
