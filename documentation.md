#         CGameEngine    


## GUI.FontHandler.Character
            
A helper class which symbols the a char from a font file
        

## UTIL.Rect
            
A rect providing info about a 2D-position and width and height either in pixels or in screen location (-1 to 1 on the x- and y-axis)
        
### Methods


#### fromPixels
converts this rect from pixel coords into screen coords based on the current display dimensions

#### toPixels
converts this rect from screencoords into pixel coords based on the current display dimensions

#### Constructor
creates a new rect with given parameters
> ##### Parameters
> **x:** the x position

> **y:** the y position

> **width:** the width for the rect

> **height:** the height for the rect

> **inScreenCoords:** are the passed values in a coord system from -1 to 1


#### Constructor
a new rect with every info = 0.0f

## Texture
            
This class is a wrapper for using textures. The implementation supports only "*.png" files. Use the SetActivationSlot(...) to set which texture slot you wanna use (GL_TEXTUREi, where i ranges from 0 to (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)).
            
                
```

... //e.g. load texture 
{
	Bind(shader);
	Bind(texture);
	//bind sampler to shader location
	glUniform1i(shader->getUniform("tex"), 0);	//only when the Sampler2D in the shader source code is called "tex"
	... //Render stuff
} // Texture and Shader are unbound automatically
```
            
        
### Methods


#### _unbind
Used to unbind the texture. This call is automated when the BIND(...) macro was used to bind this texture.

#### _bind
Used to bind the texture (using the BIND(...) macro defined in the AutoUnbind header.

#### SetActivationSlot(System.UInt32)
This method sets the slot where the texture is bound to. Valid input-range: GL_TEXTUREi, where i ranges from 0 to (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)
> ##### Parameters
> **value:** The slot you want to use.


#### Constructor
The constructor loads the image and pushes it to the GPU. Supported file extensions: .png
> ##### Parameters
> **path:** Path to file (including file extension).


## UTIL.AutoUnbind
            
This class is a wrapper for using the scopewatch. The essential idea is to have a macro (Bind(...)) which can be used to bind a child of this class and gets unbound automatically.
        
### Methods


#### _unbind
The method used to unbind this object. Has to be implemented!

#### _bind
The method used to bind this object. Has to be implemented!

## GameObject
            
A gameobject is a object in the scene. It is used as a collection of components with some additional funcionallity: Each GameObject has a transform component which is used to store the position, the rotation and the scale of that object. GameObjects are also used to handle a parent-child relation of objects (for example useful to make a player object with different attatchments).
            
Note that not every GameObject has to be visible and support some kind of renderer. It can also be used to create handlers or some other singletons.
        
### Fields

#### transform
The Transform component is assigned to each GameObject to store position scale and rotation. Note that the Parent-Child-relation has impact on the calculations taking place in the transform instance.
### Methods


#### AddComponent(ENGINE.Component*)
This method is used to assign a component to the GameObject. Note that you have to create a lasting component (using the 'new' macro).
> ##### Parameters
> **comp:** The component you want to add.

> ##### Example
> 
                
```

Component *comp = new RotateObjectComponent();
gameObject->AddComponent(comp);
```
            

#### Constructor
Note that it is strongly advised to create a GameObject using the Instantiate() method offered by the Scene or the component class.
This creates a new GameObject with a specified name.
> ##### Parameters
> **name:** The name of the new GameObject


#### Constructor
Note that it is strongly advised to create a GameObject using the Instantiate() method offered by the Scene or the component class.
This creates a new GameObject with the empty string as name.

## Component
            
This class is abstract and has to be inherited. It provides the standard functions as Start() or Update() and when added to an active GameObject instance is called by the engine. It also provides basic functionality to the engine like a ShowMouse function.
        
### Methods


#### Destroy
This function is called when the component gets destroyed.

#### Render
This function is called to render the scene (once a frame). Is called AFTER LateUpdate().

#### LateUpdate
This function is called each frame to update the component (and/or scene). Is called AFTER Update().

#### Update
This function is called each frame to update the component (and/or scene). Is called as first update function each frame.

#### Start
This function is called in the following frame after the component was created Is called AFTER Awake().

#### Awake
This function is called in the following frame after the component was created. Is called BEFORE Start().

#### SetMousePosition(System.Int32,System.Int32)
Sets the mouse position relative to the window. Note that the mouse position can be set when the mouse is not showing.
> ##### Parameters
> **x:** The target mouse position on the X-Axis in pixel.

> **y:** The target mouse position on the Y-Axis in pixel.


#### ShowMouse(System.Boolean)
Can be used to en-/disable the mouse pointer while the mouse is hovering over the window opened by the Game-Engine.
> ##### Parameters
> **showMouse:** If true the mouse is shown, if false it is not.


#### Instantiate(std.basic_string<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte>>)
Creates a new gameObject with a specified name. This GameObject is introduced to the current scene.
> ##### Parameters
> **name:** The name for the new GameObject

> ##### Return value
> A pointer to the empty gameObject with the name.

#### Instantiate
Creates a new gameObject with name "". This GameObject is introduced to the current scene.
> ##### Return value
> A pointer to the empty gameObject.

#### GetCurrentGameObject
Returns a pointer to the gameObject the component is running on/connected to.
> ##### Return value
> A pointer to the gameObject.

#### GetCurrentCamera
Returns a pointer to the current scene camera. Usefull e.g. to update the cameras location or rotation.
> ##### Return value
> A pointer to the current/active camera.

#### GetCurrentScene
Returns a handle to the active scene (to access their functionalities).
> ##### Return value
> A pointer to the active/current scene.