//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "HeaderView.h"
#import "Helper.h"
#import "LineLabel.h"
#import "ColorSelector.h"
#import "GUI.h"

#include "PositionFactory.h"
#include "Settings.h"

@implementation HeaderView

-(instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if(self){
        self.backgroundColor = [UIColor clearColor];
        imageV = nil;
        prepareL = nil;
        stageL = nil;
        timeL = nil;
        colorL = nil;
        [self addComponents];
    }
    return self;
}

-(void)addComponents{
    
    Settings &settings = PositionFactory::instance().getSettings();
    
    CGSize size = [Helper buttonSize];
    int seperator = [Helper seperator] *1.5;
    CGPoint offset = CGPointMake((self.frame.size.width - size.width*3 - seperator*2)*0.5, [Helper screenBorderOffset]);
    
    [Helper releaseViewObject:&imageV];
    imageV = [[UIImageView alloc]initWithFrame:CGRectMake(0, offset.y, self.frame.size.width, self.frame.size.height - offset.y)];
    imageV.contentMode = UIViewContentModeScaleAspectFill;
    [self addSubview:imageV];
    
    CGRect frame = CGRectMake(0, 0, 0, 0);
    frame = CGRectMake((self.frame.size.width - size.width)*0.5, offset.y, size.width, size.height);
    [self addNewLineLabel:&prepareL frame:frame  title:@"-" description:[Helper memorizeText]];
    
    frame = CGRectMake(offset.x, offset.y, size.width, size.height);
    [self addNewLineLabel:&stageL frame:frame  title:[NSString stringWithFormat:@"%d-%d", settings.getCurNumberOfRows(), settings.getCurNumberOfUsedColors()]
              description:[Helper stageText]];
    
    offset.x += seperator + size.width;
    frame = CGRectMake(offset.x, 0, size.width, size.height + offset.y);
    colorL = [[ColorSelector alloc]initWithFrame:frame];
    [self addSubview:colorL];
    [colorL addTarget:self action:@selector(changeColor:) forControlEvents:UIControlEventTouchUpInside];

    offset.x += seperator + size.width;
    frame = CGRectMake(offset.x, offset.y, size.width, size.height);
    [self addNewLineLabel:&timeL frame:frame  title:@"-" description:[Helper timeText]];

    [self showMainMenu];
}

-(void)changeColor:(id)sender{
    [((GUI*)self.superview) setNextColor];
}

-(void)setNextColor:(int)color{
    if(colorL != nil){
        color = color != -1 ? color : 0xffffff;
        [colorL setColor:color];
    }
}

-(void)addNewLineLabel:(LineLabel **)label frame:(CGRect)rect title:(NSString *)information description:(NSString *)description{
    LineLabel *object = *label;
    [Helper releaseViewObject:&object];
    object = [[LineLabel alloc]initWithFrame:rect];
    [object addLabelWithTitle:information description:description];
    [self addSubview:object];
    *label = object;
}

-(void)loadImageNamed:(NSString *)name{
    if(imageV != nil){
        float offset = [Helper screenBorderOffset];
        CGRect rect = CGRectMake(0, offset, self.frame.size.width, self.frame.size.height - offset);
        UIImage *image = [UIImage imageNamed:name];
        rect.size.width = image.size.width * rect.size.height / image.size.height;
        rect.origin.x = (self.frame.size.width - rect.size.width) *0.5;
        imageV.image = image;
        imageV.frame = rect;
    }
}

-(void)showMainMenu{
    if([self objectsNil]){
        return;
    }
    [self loadImageNamed:[Helper logoImageName]];
    imageV.hidden = false;
    stageL.hidden = true;
    prepareL.hidden = stageL.hidden;
    timeL.hidden = stageL.hidden;
    colorL.hidden = stageL.hidden;
}

-(void)showPrepareMenuWithTime:(NSTimeInterval)time{
    if([self objectsNil]){
        return;
    }
    
    prepareL.hidden = false;
    NSString *timeString = (time == 0) ? [NSString stringWithFormat:@"-"] : [NSString stringWithFormat:@"%.f", (NSTimeInterval)time];
    [prepareL setInformation: timeString];
    imageV.hidden = true;
    stageL.hidden = imageV.hidden;
    [self updateStageL];
    timeL.hidden = imageV.hidden;
    [timeL setInformation:@"-"];
    colorL.hidden = imageV.hidden;
}

-(void)showPlaceColorMenu:(NSTimeInterval)time{
    if([self objectsNil]){
        return;
    }
    [self changeColor:nil];
    timeL.hidden = false;
    NSString *timeString = (time == 0) ? [NSString stringWithFormat:@"-"] : [NSString stringWithFormat:@"%.f", (NSTimeInterval)time];
    [timeL setInformation:timeString];
    colorL.hidden = false;
    stageL.hidden = false;
    prepareL.hidden = true;
    imageV.hidden = prepareL.hidden;
}

-(void)showOverviewMenu{
    if([self objectsNil]){
        return;
    }
    
    Settings &settings = PositionFactory::instance().getSettings();
    if(settings.isLvlPassed()){
        [self loadImageNamed:[Helper deliverImageName]];
    } else {
        [self loadImageNamed:[Helper failedImageName]];
    }
    imageV.hidden = false;
    stageL.hidden = true;
    prepareL.hidden = stageL.hidden;
    timeL.hidden = stageL.hidden;
    colorL.hidden = stageL.hidden;
}

-(int)timeLabelValue{
    return [[timeL description] intValue];
}

-(int)prepareLabelValue{
    return [[prepareL description] intValue];
}

-(void)updatePrepareL:(NSTimeInterval)value{
    if([self objectsNil]){
        return;
    }
    if(value == 5){
        
    }
    [prepareL setInformation:[NSString stringWithFormat:@"%.f", value]];
}

-(void)updateTimeL:(NSTimeInterval)value{
    if([self objectsNil]){
        return;
    }
    if(value == 5){
        
    }
    [timeL setInformation:[NSString stringWithFormat:@"%.f", value]];
}

-(void)updateStageL{
    if([self objectsNil]){
        return;
    }
    Settings &settings = PositionFactory::instance().getSettings();
    [stageL setInformation:[NSString stringWithFormat:@"%d-%d", settings.getCurNumberOfRows(), settings.getCurNumberOfUsedColors()-1]];
}

-(BOOL)objectsNil{
    if(timeL == nil || stageL == nil || prepareL == nil || imageV == nil || colorL == nil){
        return true;
    }
    return false;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    ApplicationState state = PositionFactory::instance().getSettings().getApplicationState();
    if(state == GAME_MEMORIZE || state == GAME_PLACE_COLORS){
        [((GUI*)self.superview) interactWithSubmenu];
    }
}

-(void)dealloc{
    [colorL removeTarget:self action:@selector(changeColor:) forControlEvents:UIControlEventTouchUpInside];
    
    [Helper releaseViewObject:&colorL];
    [Helper releaseViewObject:&imageV];
    [Helper releaseViewObject:&prepareL];
    [Helper releaseViewObject:&stageL];
    [Helper releaseViewObject:&timeL];
    [super dealloc];
}

@end
