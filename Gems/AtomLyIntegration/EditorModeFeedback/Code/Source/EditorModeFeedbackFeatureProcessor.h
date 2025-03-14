/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <Draw/EditorStateMaskRenderer.h>
#include <Pass/EditorStatePassSystem.h>

#include <Atom/RPI.Public/FeatureProcessor.h>
#include <Atom/RPI.Reflect/System/AnyAsset.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>

namespace AZ
{
    namespace Render
    {
        //! Feature processor for Editor Mode Feedback visual effect system.
        class EditorModeFeatureProcessor
            : public RPI::FeatureProcessor
        {
        public:
            AZ_RTTI(AZ::Render::EditorModeFeatureProcessor, "{78D40D57-F564-4ECD-B9F5-D8C9784B15D0}", AZ::RPI::FeatureProcessor);

            static void Reflect(AZ::ReflectContext* context);

            // FeatureProcessor overrides ...
            void Activate() override;
            void Deactivate() override;
            void ApplyRenderPipelineChange(RPI::RenderPipeline* renderPipeline) override;
            void Render(const RenderPacket& packet) override;
            void Simulate(const SimulatePacket& packet) override;

            // RPI::SceneNotificationBus overrides ...
            void OnRenderPipelineAdded(RPI::RenderPipelinePtr pipeline) override;
            void OnRenderPipelinePassesChanged(RPI::RenderPipeline* renderPipeline) override;
            void OnRenderPipelineRemoved(RPI::RenderPipeline* pipeline) override;

        private:
            //! The pass system for the editor state feedback effects.
            AZStd::unique_ptr<EditorStatePassSystem> m_editorStatePassSystem;

            //! Map of all mask renderers for the draw tags used by the editor state feedback effects.
            AZStd::unordered_map<Name, EditorStateMaskRenderer> m_maskRenderers;

            //! Material for sending draw packets to the entity mask pass.
            Data::Instance<RPI::Material> m_maskMaterial = nullptr;
        };
    } // namespace Render
} // namespace AZ
