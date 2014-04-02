#ifndef __interface_h
#define __interface_h

//The algorithm handles simple polygons with holes. The input is
//specified as contours. The outermost contour is anti-clockwise, while
//all the inner contours must be clockwise. No point should be repeated
//in the input. A sample input file 'data_1' is provided.
//
//
//The output is a list of triangles. Each triangle gives a pair
//(i, j, k) where i, j, and k are indices of the vertices specified in
//the input array. (The index numbering starts from 1, since the first
//location v[0] in the input array of vertices is unused). The number of
//output triangles produced for a polygon with n points is,
//	(n - 2) + 2*(#holes)
//
//
//The algorithm also generates a qyery structure which can be
//used to answer point-location queries very fast.
//
//int triangulate_polygon(...)
//Time for triangulation: O(n log*n)
//		
//int is_point_inside_polygon(...)	
//Time for query: O(log n)
//
//Both the routines are defined in 'tri.c'. See that file for
//interfacing details.  If not used stand_alone, include the header file
//"interface.h" which contains the declarations for these
//functions. Inclusion of "triangulation.h" is not necessary.
//
//
//The implementation uses statically allocated arrays. Choose
//appropriate value for SEGSIZE /* in triangulate.h */ depending on
//input size.
//
//
//There sould not be any compilation problem. If log2() is not
//defined in your math library, you will have to supply the definition.
//

#ifndef TRUE       // dd
#define TRUE 1
#endif             // dd
#ifndef FALSE      // dd
#define FALSE 0
#endif             // dd

#ifdef __cplusplus // dd
extern "C" {       // dd
#endif             // dd

extern int triangulate_polygon(int, int *, double (*)[2], int (*)[3]);
extern int is_point_inside_polygon(double *);

#ifdef __cplusplus // dd
}                  // dd
#endif             // dd

#endif /* __interface_h */
