//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "SettingsViewController.h"
#import "Helper.h"
#import "SettingsButton.h"
#import "SettingsContent.h"
#include "PositionFactory.h"


@implementation SettingsViewController

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super init];
    if(self != nil){
        datas = nil;
        settings = NULL;
        datas = [[Helper getSettingsConent]mutableCopy];
        settings = &PositionFactory::instance().getSettings();
        self.view.frame = frame;
        [self addSettingsButton];
    }
    return self;
}

-(void)addSettingsButton{
    if(datas == nil || settings == NULL){
        NSLog(@"Error in SettingsViewController method addSettingsButton");
        return;
    }
    int width = (int)(self.view.frame.size.width * 0.25);
    int itemsPerRow = 2;
    float spacing = width * 0.3;
    
    offset = CGPointMake((self.view.frame.size.width - width * itemsPerRow - spacing) * 0.5, (self.view.frame.size.height - width * itemsPerRow - spacing) * 0.5 );
    for(int i=0; i<datas.count; i++){
        SettingsContent *content = [datas objectAtIndex:i];
        SettingsButton *imageV = [[SettingsButton alloc]initWithId:i frame:CGRectMake(offset.x, offset.y, width, width) content:content];
        [self.view addSubview:imageV];
        offset.x += imageV.frame.size.width + spacing;
        if(((i+1) % itemsPerRow) == 0){
            offset.x = (self.view.frame.size.width - width * itemsPerRow - spacing) * 0.5;
            offset.y += imageV.frame.size.height + spacing;
        }
        [imageV release];
        imageV = nil;
    }
}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

-(void)viewDidLoad{
    [super viewDidLoad];
}

-(void)dealloc{
    UIView *controllerView = self.view;
    [Helper releaseMutableContainer:&datas];
    [Helper removeSubviewsFromParent:&controllerView];
    settings = NULL;
    [super dealloc];
}

@end
