//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "SettingsContent.h"

@implementation SettingsContent
@synthesize title;
@synthesize information;
@synthesize selected;
@synthesize color;
@synthesize selectedImageName;
@synthesize unselectedImageName;

-(instancetype)init{
    self = [super init];
    if(self != nil){
        [self setDefaultValues];
    }
    return self;
}

-(void)setDefaultValues{
    self.title = nil;
    self.information = nil;
    self.selectedImageName = nil;
    self.unselectedImageName = nil;
    self.selected = false;
    self.color = 0x000000;
}

-(void)dealloc{
    [super dealloc];
}

@end
