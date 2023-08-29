using System;
using System.Collections.Generic;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using SNEditor.EngineAPIStructs;
using SNEditor.Components;

namespace SNEditor.EngineAPIStructs
{
    [StructLayout (LayoutKind.Sequential)]
    class TransformComponent
    {
        public Vector3 Position;
        public Vector3 Rotation;
        public Vector3 Scale = new Vector3(1, 1, 1);
    }

    [StructLayout(LayoutKind.Sequential)]
    class GameEntityDescriptor
    {
        public TransformComponent Transform = new TransformComponent();
    }
}

namespace SNEditor.DllWrappers
{
    static class EngineAPI
    {
        private const string _dllName = "SNEngineDLL.dll";

        [DllImport(_dllName)]

        private static extern int CreateGameEntity(GameEntityDescriptor desc);
        public static int CreateGameEntity(GameEntity entity)
        {
            GameEntityDescriptor desc = new GameEntityDescriptor();

            // Transform component
            {
                var c = entity.GetComponent<Transform>();
                desc.Transform.Position = c.Position;
                desc.Transform.Rotation = c.Rotation;
                desc.Transform.Scale = c.Scale;
            }

            return CreateGameEntity(desc);
        }

        [DllImport(_dllName)]

        private static extern void RemoveGameEntity(int id);

        public static void RemoveGameEntity(GameEntity entity)
        {
            RemoveGameEntity(entity.EntityId);
        }

    }
}
