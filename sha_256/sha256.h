

















//#define ROTR(x, n) 		(( (x) >> (n) ) | ((x) << (32-(n))))
//#define SHR(x, n) 		((x) >> (n))
//#define CH(x,y,z) 		(((x) & (y)) ^ ((~(x)) & (z)))
//#define MAJ(x,y,z) 		(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
//#define CAP_SIGMA0(x) 	(ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
//#define CAP_SIGMA1(x) 	(ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
//#define SIGMA0(x) 		(ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
//#define SIGMA1(x) 		(ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))