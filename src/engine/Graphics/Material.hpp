#ifndef ENGINE_MATERIAL
#define ENGINE_MATERIAL

#include "Shader.hpp"
#include <map>

namespace Engine::Graphics {

  enum MaterialParameterType {
    FLOAT,
    INT,
    VEC2,
    VEC3,
    VEC4
  };

  /**
   * @brief an semi-abstract class that represents a material to a shader
   * 
   * This class is used to create a material that can be used with a shader.
   * Materials are used to pass data to the shader, and to tell the shader how
   * to handle that data. To create a material, you must first assign a shader
   * to the material. From there, you tell the material what the parameters of
   * the shader are, and what values the shader should use for those parameters.
   * This is done with the `CreateParameter` and `SetParameter` methods.
   * 
   * ## Examples
   * 
   * There are two ways to create a materials:
   * 
   * - Using the default constructor
   * 
   * - Deriving from this class (Recommended if your shader is being used in 
   * multiple places)
   */
  class Material {
    private:
    Shader* m_referenceShader;

    std::map<const char*, MaterialParameterType> m_parameters;
    std::map<const char*, void*> m_parameterValues;

    public:
    
    /**
     * @brief The default constructor
     * 
     * Takes in a shader to use as a reference for the material.
     */
    Material(Shader* referenceShader = &DefaultShader);

    /**
     * @brief Creates a parameter for the material
     * 
     * This method takes in a parameter name and a parameter type and keeps track
     * of the parameters in the material. This method will throw an error if the
     * parameter already exists.
     * 
     * @param name The name of the parameter
     * @param type The type of the parameter
     */
    void CreateParameter(const char* name, MaterialParameterType type);

    /**
     * @brief Sets the value of a parameter
     * 
     * This method takes a reference to a value and assigns it to the parameter
     * with the specified name. This method will throw an error if the parameter
     * does not exist.
     * 
     * You can either pass a dynamic variable, or a pointer to an existing value.
     * There is however no pointer safety, but the method returns a void pointer
     * to the value that was set.
     * 
     * @param name The name of the parameter
     * @param value The value to assign to the parameter
     * 
     * @returns A void pointer to the value that was set. Should be cast to the
     * correct type.
     * 
     * @warning This method does not check if the input value is the correct type. 
     * If there is a mismatch, the program will potentially segfault, or 
     * lead to undefined behavior.
     */
    void* SetParameter(const char* name, void* value); 

    /**
     * @brief Applies both the material values to the shader
     * 
     * This method gets called by the renderer when the material is applied.
     * 
     */
    void ApplyMaterialParams();

    /**
     * @brief Gets the shader used by the material
     * 
     * @reutnrs The shader used by the material
     */
    Shader* GetShader();
  };
}

#endif