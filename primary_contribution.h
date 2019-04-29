#pragma once

#include "redner.h"
#include "buffer.h"
#include "vector.h"
#include "intersection.h"
#include "area_light.h"
#include "texture.h"

struct Scene;
struct ChannelInfo;

/**
 * Accumulate the contribution for the first hit, including light source emission, AOV channels
 * such as depth, alpha, normal, etc.
 */
void accumulate_primary_contribs(
        const Scene &scene,
        const BufferView<int> &active_pixels,
        const BufferView<Vector3> &throughputs,
        const BufferView<Real> &channel_multipliers,
        const BufferView<Ray> &incoming_rays,
        const BufferView<RayDifferential> &incoming_ray_differentials,
        const BufferView<Intersection> &shading_isects,
        const BufferView<SurfacePoint> &shading_points,
        const Real weight,
        const ChannelInfo &channel_info,
        float *rendered_image,
        BufferView<Real> edge_contribs);

/// Backprop version of the function above.
void d_accumulate_primary_contribs(
        const Scene &scene,
        const BufferView<int> &active_pixels,
        const BufferView<Vector3> &throughputs,
        const BufferView<Real> &channel_multipliers,
        const BufferView<Ray> &incoming_rays,
        const BufferView<RayDifferential> &incoming_ray_differentials,
        const BufferView<Intersection> &shading_isects,
        const BufferView<SurfacePoint> &shading_points,
        const Real weight,
        const ChannelInfo &channel_info,
        const float *d_rendered_image,
        BufferView<DAreaLightInst> d_direct_lights,
        BufferView<DTexture3> d_envmap_vals,
        BufferView<Matrix4x4> d_world_to_envs,
        BufferView<DRay> d_incoming_rays,
        BufferView<RayDifferential> d_incoming_ray_differentials,
        BufferView<SurfacePoint> d_shading_points,
        BufferView<DTexture3> d_diffuse_texs,
        BufferView<DTexture3> d_specular_texs,
        BufferView<DTexture1> d_roughness_texs);