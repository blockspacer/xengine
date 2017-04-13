//
//  ASSET_EDITOR.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "ASSET_EDITOR.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "CORE_HELPERS_CALLBACK.h"

ASSET_EDITOR::ASSET_EDITOR() :
    CORE_APPLICATION(),
    DefaultFileystem(),
    InterfaceCamera(),
    BaseUiScreen() {
    
#if PLATFORM_OSX
        DefaultFileystem.Initialize( "/Users/CBE/DevelopProjects/game-engine-clean/RESOURCES/" );
#elif PLATFORM_IOS
        DefaultFileystem.Initialize( "None" );
#elif PLATFORM_ANDROID
        //DefaultFileystem.Initialize( "None" );
#elif PLATFORM_WINDOWS
        DefaultFileystem.Initialize( "C:\\Users\\X\\Documents\\game-engine-clean\\RESOURCES\\" );
#endif
        
        CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
        
    SetApplicationInstance( *this );
}

ASSET_EDITOR::~ASSET_EDITOR() {
    
}

void ASSET_EDITOR::Initialize() {
    
    CORE_HELPERS_CALLBACK * myCallback = new CORE_HELPERS_CALLBACK( &Wrapper<CORE_APPLICATION, &CORE_APPLICATION::Render>, this );
    
    CORE_HELPERS_CALLBACK_2<int, int> resizeCallback( &Wrapper2<ASSET_EDITOR, int, int, &ASSET_EDITOR::OnScreenResized>, this );
    
    GRAPHIC_RENDERER::GetInstance().Initialize();
    GRAPHIC_RENDERER::GetInstance().SetRenderCallback( myCallback );
    GRAPHIC_RENDERER::GetInstance().SetResizeViewCallback( resizeCallback );
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() ) );
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    
    interface_lookat.Normalize();
    
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight(), CORE_MATH_VECTOR(0.0f, 0.0f), interface_lookat );
    
    BaseUiScreen.GetPlacement().Initialize( NULL, CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR(ApplicationWindow->GetWidth(), ApplicationWindow->GetHeight()), GRAPHIC_UI_Center );
    BaseUiScreen.Initialize();
    
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize(CORE_MATH_VECTOR( GetApplicationWindow().GetWidth(), GetApplicationWindow().GetHeight() ) );
    GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(&BaseUiScreen, "BaseView" );
}

void ASSET_EDITOR::Finalize() {
    
}

void ASSET_EDITOR::Update( float time_step ) {
    
    GRAPHIC_UI_SYSTEM::GetInstance().Update(time_step);
}

void ASSET_EDITOR::Render() {
    
    GRAPHIC_RENDERER::GetInstance().SetCamera( InterfaceCamera );
    
    GRAPHIC_UI_SYSTEM::GetInstance().Render( GRAPHIC_RENDERER::GetInstance() );
}

GRAPHIC_UI_ELEMENT * ASSET_EDITOR::CreateItem( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor ) {
    
    GRAPHIC_UI_ELEMENT * element = new GRAPHIC_UI_ELEMENT;
    
    element->SetIdentifier( CORE_HELPERS_IDENTIFIER( item_name ) );
    element->GetPlacement().Initialize(&BaseUiScreen.GetPlacement(), position, size, anchor);
    
    element->Initialize();
    BaseUiScreen.AddObject( element );
    
    return element;
}

GRAPHIC_UI_FRAME * ASSET_EDITOR::CreateFrame( const char * item_name, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & size, int anchor ) {
    
    GRAPHIC_UI_FRAME * frame = new GRAPHIC_UI_FRAME;
    
    frame->SetIdentifier( CORE_HELPERS_IDENTIFIER( item_name ) );
    frame->SetPosition( position );
    frame->GetPlacement().SetSize( size );
    
    return frame;
}

GRAPHIC_UI_RENDER_STYLE * ASSET_EDITOR::SetStyleForItem( int state, GRAPHIC_UI_ELEMENT * element, const char * texture_name, const CORE_HELPERS_COLOR & color ) {
    
    GRAPHIC_UI_RENDER_STYLE * default_style = new GRAPHIC_UI_RENDER_STYLE;
    
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, default_style );
    
    return default_style;
}

void ASSET_EDITOR::OnScreenResized( int width, int height ) {
    
    CORE_MATH_QUATERNION interface_lookat( 0.0f, 0.0f, 0.0f, 1.0f );
    CORE_MATH_VECTOR size( width, height );
    GRAPHIC_UI_SYSTEM::GetInstance().SetScreenSize( size );
    BaseUiScreen.GetPlacement().SetSize(size);
    
    delete InterfaceCamera;
    InterfaceCamera = new GRAPHIC_CAMERA_ORTHOGONAL( 1.0f, 100.0f, width, height, CORE_MATH_VECTOR(0.0f, 0.0f), interface_lookat );
}
