//
//  TutorialViewController.m
//  spin
//
//  Created by schr3da on 17/07/15.
//
//

#import <Foundation/Foundation.h>
#import "TutorialViewController.h"
#import "LabelButton.h"
#import "Helper.h"
#import "GUI.h"

@implementation TutorialViewController
@synthesize isVisible;
    
-(instancetype)initWithStrings:(NSArray *)array parentRef:(GUI *)ref initCounter:(int)number{
    if(array == nil || ref == nil){
        NSLog(@"Error during init - stringarray or gui ref is nil in TutorialViewController");
        return nil;
    }
    self = [super init];
    if(self != nil){
        CGRect screenSize = [UIScreen mainScreen].bounds;
        stepCounter = 0;
        initCounterNumber = number;
        isVisible = false;
        guiRef = ref;
        [Helper releaseObject:&strings];
        strings = [array mutableCopy];
        [Helper releaseViewObject:&contentView];
        contentView = [[UIView alloc]initWithFrame:CGRectMake(0,
                                                               screenSize.size.height,
                                                               screenSize.size.width,
                                                               screenSize.size.height - screenSize.size.height *0.65)];
        self.view = contentView;
        self.view.backgroundColor = [UIColor whiteColor];
        [self addButtons];
    }
    return self;
}

-(void)addInstructionWithTitle:(NSString *)title text:(NSString *)text{
    [Helper releaseViewObject:&headerL];
    headerL = [[UILabel alloc]initWithFrame:CGRectMake((self.view.frame.size.width - self.view.frame.size.width *0.9)*0.5,
                                                       0,
                                                       self.view.frame.size.width *0.9,
                                                       self.view.frame.size.width *0.08)];
    headerL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size: headerL.frame.size.height];
    headerL.textColor = [Helper getGrayColor];
    headerL.textAlignment = NSTextAlignmentCenter;
    headerL.text = title;
    [self.view addSubview:headerL];
    
    [Helper releaseViewObject:&textL];
    textL = [[UILabel alloc]initWithFrame:CGRectMake((self.view.frame.size.width - self.view.frame.size.width *0.9)*0.5,
                                                       headerL.frame.origin.y + headerL.frame.size.height*1.5,
                                                       self.view.frame.size.width *0.9,
                                                       self.view.frame.size.width *0.12)];
    textL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size: textL.frame.size.height*0.4];
    textL.textColor = [Helper getGrayColor];
    textL.textAlignment = NSTextAlignmentCenter;
    textL.numberOfLines = 2;
    textL.text = text;
    [self.view addSubview:textL];

}

-(void)addButtons{
    CGSize buttonSize = [Helper buttonSize];
    [Helper releaseViewObject:&nextB];
    nextB = [[LabelButton alloc]initWithFrame:CGRectMake((self.view.frame.size.width - buttonSize.width)*0.5,
                                                         self.view.frame.size.height - buttonSize.height - [Helper screenBorderOffset],
                                                         buttonSize.width, buttonSize.height)];
    [nextB addLabelWithTitle:[Helper nextLevelText] andImage:[UIImage imageNamed:@"nextIcon"]];
    [nextB addTarget:self action:@selector(next:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:nextB];
    
    [self next:nil];
}

-(void)next:(id)sender{
    if(guiRef == nil){
        return;
    }
    stepCounter++;
    if(strings != nil && [strings count] >= stepCounter){
        [self addInstructionWithTitle: [NSString stringWithFormat:@"%@ %d", [Helper tutorialTitle], stepCounter + initCounterNumber]
                                 text:[strings objectAtIndex:stepCounter-1]];
        if(stepCounter == [strings count]){
            Settings &settings = PositionFactory::instance().getSettings();
            [((GUI *)guiRef)addGameTimer:settings.getInitTime()];
            [nextB setNewTitle:[Helper dismissText] andImageWithName:@"readyIcon"];
        }
    } else {
        [self hide];
    }
}

-(void)show{
    if(!isVisible){
    [self animateWithToNewYValue: guiRef.frame.size.height - self.view.frame.size.height ];
        isVisible = true;
    }
}

-(void)hide{
    if(isVisible){
        [self animateWithToNewYValue: guiRef.frame.size.height];
        isVisible = false;
    }
}

-(void)animateWithToNewYValue:(float)yValue{
    CGRect newFrame = CGRectMake(self.view.frame.origin.x, yValue, self.view.frame.size.width, self.view.frame.size.height);
    [UIView animateWithDuration:[Helper animationTime] animations:^{
        self.view.frame = newFrame;
    }];
}

-(void)dealloc{
    
    [Helper releaseObject:&strings];
    [Helper releaseViewObject:&headerL];
    [Helper releaseViewObject:&nextB];
    [Helper removeSubviewsFromParent:&contentView];
    [Helper releaseViewObject:&contentView];
    guiRef = nil;
    headerL = nil;
    contentView = nil;
    [super dealloc];
}

@end