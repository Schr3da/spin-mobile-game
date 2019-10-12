//
//  SettingsButton.m
//  spin
//
//  Created by schr3da on 05/06/15.
//
//

#import "SettingsButton.h"
#import "SettingsContent.h"
#import "Helper.h"
#include "PositionFactory.h"

@implementation SettingsButton
@synthesize bId;

-(instancetype)initWithId:(int)bIdRef frame:(CGRect)frame content:(SettingsContent *)contentRef{
    self = [super initWithFrame:frame];
    if(contentRef != nil && self != nil){
        int insets = (int)(self.frame.size.width *0.1);
        bId = bIdRef;
        content = contentRef;
        settings = &PositionFactory::instance().getSettings();
        self.imageEdgeInsets = UIEdgeInsetsMake(insets,insets,insets,insets);
        self.backgroundColor = [Helper getIUColorFromHex: content.color];
        [self setImageBasedOnState];
        [self addTarget:self action:@selector(preAction:) forControlEvents:UIControlEventTouchDown];
                [self addTarget:self action:@selector(preAction:) forControlEvents:UIControlEventTouchUpOutside];
        [self addTarget:self action:@selector(performAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return self;
}

-(void)preAction:(id)sender{
    self.alpha = (self.alpha == 1.f) ? 0.8f : 1.f;
}

-(void)performAction:(id)sender{
    self.alpha = 1;
    if(content == nil || settings == NULL){
        return;
    }
    if([content.information isEqualToString:[Helper settingsSoundText]]){
        settings->setSound(content.selected);
    } else if([content.information isEqualToString:[Helper settingsVibrationText]]){
        settings->setVibration(content.selected);
    } else if([content.information isEqualToString:[Helper tutorialTitle]]){
        settings->setTutorialActiveState(content.selected);
        settings->setNewGameDefaultValues();
    } else if([content.information isEqualToString:[Helper settingsSnapToGridText]]){
        settings->setSnapToGrid(content.selected);
    }
    [self setImageBasedOnState];
}

-(void)setImageBasedOnState{
    if(content == nil || settings == NULL){
        return;
    }
    UIImage *image = nil;
    content.selected = !content.selected;
    if(content.selected){
        image = [UIImage imageNamed:content.unselectedImageName];
    } else {
        image = [UIImage imageNamed:content.selectedImageName];
    }
    [self setImage:image forState:UIControlStateHighlighted];
    [self setImage:image forState:UIControlStateNormal];
}

-(void)dealloc{
    [self removeTarget:self action:@selector(preAction:) forControlEvents:UIControlEventTouchDown];
    [self removeTarget:self action:@selector(performAction:) forControlEvents:UIControlEventTouchUpInside];
    content = nil;
    settings = NULL;
    [super dealloc];
}

@end;
