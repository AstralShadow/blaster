#ifndef INCLUDE_GEOMETRY_HPP
#define INCLUDE_GEOMETRY_HPP

#include <SDL2/SDL_rect.h>

/**
 * Returns if two segments intersect.
 *
 * Puts the intersection point in *result.
 */
bool segment_intersection(SDL_FPoint p1,
                          SDL_FPoint p2,
                          SDL_FPoint p3,
                          SDL_FPoint p4,
                          SDL_FPoint* p_out = nullptr);

#endif // INCLUDE_GEOMETRY_HPP
