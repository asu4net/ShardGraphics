#pragma once

namespace Shard::Graphics
{
    class Camera;
    
    class CameraController
    {
    public:
        CameraController(Camera* camera);
        
        void Attach();
        void Update(float deltaTime);
        void Detach();
    
        Camera* GetCamera() const { return m_Camera; }
        
    protected:
        virtual void OnAttach();
        virtual void OnUpdate(float deltaTime);
        virtual void OnDetach();
        
    private:
        Camera* m_Camera;
    };
}
