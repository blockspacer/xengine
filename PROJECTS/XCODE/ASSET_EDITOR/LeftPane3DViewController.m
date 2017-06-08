//
//  LeftPane3DViewController.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "LeftPane3DViewController.h"
#import "Cpp3dDataProxy.h"
#import "GAMEPLAY_COMPONENT_ENTITY.h"
#import "GAMEPLAY_COMPONENT_MANAGER.h"
#import "ASSET_EDITOR.h"
#import "Constants.h"
#import "Create3dItem.h"
#import "GAMEPLAY_COMPONENT_POSITION.h"
#import "GAMEPLAY_COMPONENT_RENDER.h"
#import "GAMEPLAY_COMPONENT_PHYSICS.h"
#import "GAMEPLAY_COMPONENT_SCRIPT.h"
#import "GAMEPLAY_COMPONENT_ANIMATION.h"
#import "ResourceManager.h"
#import "CORE_ABSTRACT_PROGRAM_LUA.h"
#import "CORE_ABSTRACT_RUNTIME_LUA.h"
#import "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.h"

@interface LeftPane3DViewController ()

@end

@implementation LeftPane3DViewController {
    NSString * ResourceType;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    self.custom3dTableViewDelegate = [[Custom3dTableViewDelegate alloc] init];
    
    [self.ComponentsTableView registerNib:[[NSNib alloc] initWithNibNamed:@"PositionComponent" bundle:[NSBundle mainBundle]] forIdentifier:@"PositionComponent"];
    [self.ComponentsTableView registerNib:[[NSNib alloc] initWithNibNamed:@"RenderComponent" bundle:[NSBundle mainBundle]] forIdentifier:@"RenderComponent"];
    [self.ComponentsTableView registerNib:[[NSNib alloc] initWithNibNamed:@"PhysicsComponent" bundle:[NSBundle mainBundle]] forIdentifier:@"PhysicsComponent"];
    [self.ComponentsTableView registerNib:[[NSNib alloc] initWithNibNamed:@"ScriptComponent" bundle:[NSBundle mainBundle]] forIdentifier:@"ScriptComponent"];
    [self.ComponentsTableView registerNib:[[NSNib alloc] initWithNibNamed:@"EmptyComponent" bundle:[NSBundle mainBundle]] forIdentifier:@"EmptyComponent"];
    
    self.ComponentsTableView.delegate = self.custom3dTableViewDelegate;
    self.ComponentsTableView.dataSource = self.custom3dTableViewDelegate;
    self.custom3dTableViewDelegate.ParentVCDelegate = self;
}

-(void)viewDidAppear {
    [self.ComponentsTableView reloadData];
}

- (IBAction)CreateItem:(id)sender {
    
    [self performSegueWithIdentifier:@CREATE_3D_ITEM_SEGUE sender:self];
}

- (void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
    
    if( [[segue identifier] isEqualToString:@CREATE_3D_ITEM_SEGUE] ) {
        Create3dItem * ci = [segue destinationController];
        
        ci.BackDelegate = self;
    }
    else if( [[segue identifier] isEqualToString:@CHOOSE_RESOURCE_SEGUE] ) {
        ResourceManager * rma = segue.destinationController;
        
        rma.ResourceDelegate = self;
        
        rma.ResourceType = ResourceType;
    }
    else {
        abort();
    }
}

-(void) OnBack {
    
    [self.OutlineView reloadData];
}

-(void) onItemCollectionChanged {
    
    [self.OutlineView reloadData];
}

-(void)outlineViewSelectionDidChange:(NSNotification *)notification {
    
    self.custom3dTableViewDelegate.Entity = [self.OutlineView itemAtRow:[self.OutlineView selectedRow]];
    
    [self.ComponentsTableView reloadData];
    
    auto viewer = ( (ASSET_EDITOR*) &ASSET_EDITOR::GetApplicationInstance())->Get3dViewer();
    viewer->SetSelectedEntity( self.custom3dTableViewDelegate.Entity.Entity );
}

-(BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item {
    
    Cpp3dDataProxy * itemProxy = item;
    
    GAMEPLAY_COMPONENT_ENTITY * entity = itemProxy.Entity;
    
    if ( entity == NULL ) {
        return NO;
    }
    
    for (int i =0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++) {
        
        if ( entity->GetChild( i ) != NULL) {
            return YES;
        }
    }
    
    return NO;
}

-(NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item {
    
    if ( item != nil ) {
        
        Cpp3dDataProxy * itemProxy = item;
        
        GAMEPLAY_COMPONENT_ENTITY * entity = itemProxy.Entity;
        
        if ( entity == NULL ) {
            return NO;
        }
        
        int count = 0;
        
        for (int i =0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++) {
            
            if ( entity->GetChild( i ) != NULL) {
                count++;
            }
        }
        
        return count;
    }
    else {
        
        static bool hack = true;
        
        if ( hack ) {
            hack = false;
            return 0;
        }
        
        int count = 0;
        
        for ( int i =0; i < 2048; i++ ) {
            
            auto v = &GAMEPLAY_COMPONENT_MANAGER::GetInstance();
            
            if ( v && GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEntity( i ) != NULL ) {
                count++;
            }
            else {
                break;
            }
        }
        
        return count;
    }
}

-(void)outlineView:(NSOutlineView *)outlineView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    
    /*NSInteger col = [[outlineView tableColumns ] indexOfObject:tableColumn];
    
    CppUIDataProxy * itemProxy = item;
    
    CORE_MATH_VECTOR size = itemProxy.Element->GetPlacement().GetSize();
    CORE_MATH_VECTOR position = itemProxy.Element->GetPlacement().GetRelativePosition();
    
    NSString * str = object;
    
    switch (col) {
        case 0:
            
            break;
        case 1:
            
            position.X( str.floatValue );
            break;
        case 2:
            
            position.Y( str.floatValue );
            break;
        case 3:
            
            size.X( str.floatValue );
            break;
        case 4:
            
            size.Y( str.floatValue );
            break;
            
    }
    
    itemProxy.Element->GetPlacement().SetSize( size );
    itemProxy.Element->GetPlacement().SetRelativePosition( position );*/
}

-(id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item {
    
    Cpp3dDataProxy * proxy = [[Cpp3dDataProxy alloc] init];
    
    proxy.Entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEntity(index);
    
    return proxy;
}

-(id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    
    Cpp3dDataProxy * proxy = item;
    
    if ( proxy.Entity == NULL )
        return @"1";
    
    /*NSInteger col = [[outlineView tableColumns ] indexOfObject:tableColumn];
    
    switch (col) {
        case 0:
            
            return [NSString stringWithFormat:@"%s", proxy.Entity->GetIdentifier().GetTextValue()];
        case 1:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetRelativePosition().X()];
        case 2:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetRelativePosition().Y()];
        case 3:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetSize().X()];
        case 4:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetSize().Y()];
            
        default:
            return @"0";
    }*/
    
    return @"2";
}

-(void) CreateComponent:(NSView *) row {
    
    int r = [self.ComponentsTableView rowForView:row];
    
    if( r == (int) GAMEPLAY_COMPONENT_TYPE_Position ) {
        
        auto comp = new GAMEPLAY_COMPONENT_POSITION();
        
        [[self.custom3dTableViewDelegate Entity] Entity]->SetCompononent(comp, GAMEPLAY_COMPONENT_TYPE_Position);
    }
    else if( r == (int) GAMEPLAY_COMPONENT_TYPE_Render ) {
        
        auto comp = new GAMEPLAY_COMPONENT_RENDER();
        
        [[self.custom3dTableViewDelegate Entity] Entity]->SetCompononent(comp, GAMEPLAY_COMPONENT_TYPE_Render);
    }
    else if( r == (int) GAMEPLAY_COMPONENT_TYPE_Animation ) {
        
        auto comp = new GAMEPLAY_COMPONENT_ANIMATION();
        
        [[self.custom3dTableViewDelegate Entity] Entity]->SetCompononent(comp, GAMEPLAY_COMPONENT_TYPE_Animation);
    }
    else if( r == (int) GAMEPLAY_COMPONENT_TYPE_Script ) {
        
        auto comp = new GAMEPLAY_COMPONENT_SCRIPT();
        
        [[self.custom3dTableViewDelegate Entity] Entity]->SetCompononent(comp, GAMEPLAY_COMPONENT_TYPE_Script);
    }
    else if( r == (int) GAMEPLAY_COMPONENT_TYPE_Physics ) {
        
        auto comp = new GAMEPLAY_COMPONENT_PHYSICS();
        
        [[self.custom3dTableViewDelegate Entity] Entity]->SetCompononent(comp, GAMEPLAY_COMPONENT_TYPE_Physics);
    }
    else {
        abort();
    }
    
    [self.ComponentsTableView reloadData];
}

-(void) SelectObject3d {
    
    ResourceType = @"Model";
    
    [self performSegueWithIdentifier:@CHOOSE_RESOURCE_SEGUE sender:self];
}

-(void) SelectEffect {
    
    ResourceType = @"Effect";
    [self performSegueWithIdentifier:@CHOOSE_RESOURCE_SEGUE sender:self];
}

-(void) SelectScript {
    
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];
    [openDlg setTitle:@"Select your script file"];
    
    // Enable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:NO];
    
    // Display the dialog.  If the OK button was pressed,
    // process the files.
    if ( [openDlg runModal] == NSModalResponseOK )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg filenames];
        NSString * script_path =[files objectAtIndex:0];
        
        CORE_ABSTRACT_PROGRAM_LUA * program = new CORE_ABSTRACT_PROGRAM_LUA();
        CORE_ABSTRACT_RUNTIME_LUA * runtime = (CORE_ABSTRACT_RUNTIME_LUA *) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[ CORE_ABSTRACT_PROGRAM_RUNTIME_Lua ];
        
        program->Load([script_path cStringUsingEncoding:NSASCIIStringEncoding], *runtime );
        program->Execute();
        
        auto cmp = (GAMEPLAY_COMPONENT_SCRIPT *) [self.custom3dTableViewDelegate.Entity Entity]->GetComponent( GAMEPLAY_COMPONENT_TYPE_Script );
        
        if ( cmp == NULL ) {
            
            cmp = (GAMEPLAY_COMPONENT_SCRIPT *) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Script );
            
            [self.custom3dTableViewDelegate.Entity Entity]->SetCompononent(cmp, GAMEPLAY_COMPONENT_TYPE_Script );
        }
        
        auto app = (ASSET_EDITOR *) (&CORE_APPLICATION::GetApplicationInstance());
        
        cmp->SetScript( program );
        
        ( ( GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT * ) app->Get3dViewer()->GetScene()->GetUpdatableSystemTable()[3] )->AddEntity( [self.custom3dTableViewDelegate.Entity Entity] );
    }
    
    //TODO:
    //ResourceType = @"Script";
    //[self performSegueWithIdentifier:@CHOOSE_RESOURCE_SEGUE sender:self];
}

-(void) OnResourceSelected:(ResourceProxy *)Resource {
    
    if ( [ResourceType isEqualToString:@"Model"]) {
        
        auto cmp = (GAMEPLAY_COMPONENT_RENDER* ) [[self.custom3dTableViewDelegate Entity] Entity]->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render);
        
        auto proxy = new RESOURCE_PROXY;
        proxy->SetResource( Resource.Object3d );
        cmp->SetObject( proxy );
    } else if ( [ResourceType isEqualToString:@"Effect"] ) {
        
        auto cmp = (GAMEPLAY_COMPONENT_RENDER* ) [[self.custom3dTableViewDelegate Entity] Entity]->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render);
        
        auto proxy = new RESOURCE_PROXY;
        proxy->SetResource( Resource.Effect );
        cmp->SetEffect( proxy );
    }
    
    ResourceType = @"";
}

@end