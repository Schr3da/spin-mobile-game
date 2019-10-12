var Score = require('./models/score');

module.exports = function(app) {
    app.get('/api/score', function(req, res) {
        Score.find({}).sort({
            score: -1
        }).exec(function(err, scores) {
            if (err)
                res.send(err);
            console.log("Scores sent");
            res.json(scores);
        });
    });

    app.post('/api/score', function(req, res) {
        var score = new Score();
        var points = req.body.score;
        score.score = points;
        score.save(function(err) {
            if (err)
                res.send(err);
            console.log('score successful saved: ' + points);

            Score.find({}).sort({
                score: -1
            }).exec(function(err, scores) {
                if (err)
                    res.send(err);
                for (var i = 0; i < scores.length; i++) {
                    if (scores[i].score == points) {
                        res.json(i);
                        break;
                    }
                }
            });

        });

    });
};
